/*
 * Driver for the Player server.
 * 2012 Aleksey Timin
 *
 * Public Domain
 * */
#include <math.h>
#include <libplayercore/playercore.h>
#include <modbus/modbus.h>
#include <sstream>

class BotDriver : public ThreadedDriver {
public:
  BotDriver(ConfigFile* cf, int section)
      : ThreadedDriver(cf, section, false, PLAYER_MSGQUEUE_DEFAULT_MAXLEN)
  {
    this->AddInterface(&this->aio_addr, cf, section, PLAYER_AIO_CODE);
    this->AddInterface(&this->actarray_addr, cf, section, PLAYER_ACTARRAY_CODE);

    this->port = (char*)cf->ReadFilename(section, "port", NULL);
    this->baud = cf->ReadInt(section, "baud", 9600);
    this->uid = cf->ReadInt(section, "uid", 1);
  }

  ~BotDriver() 
  {
    modbus_close(this->ctx);
    modbus_free(this->ctx);
  }

private:
  modbus_t *ctx;
  char* port;
  int baud;
  int uid;


  player_devaddr_t  aio_addr;
  player_devaddr_t  actarray_addr;

  virtual int ProcessMessage(QueuePointer &resp_queue, 
                                player_msghdr* hdr,
                                void* data)
  {
    // Process messages here.  Send a response if necessary, using Publish().
    // If you handle the message successfully, return 0.  Otherwise,
    // return -1, and a NACK will be sent for you, if a response is required.
    printf("Got message for interf=%d type=%d and subtype=%d\n", 
        hdr->addr.interf, hdr->type, hdr->subtype);

    switch (hdr->type) {
      case PLAYER_MSGTYPE_CMD:
        switch(hdr->subtype) {
          case PLAYER_ACTARRAY_CMD_POS:
            player_actarray_position_cmd *cmd = (player_actarray_position_cmd*)data;
            int degs = (int)round(cmd->position * 57.29);
            int joint = cmd->joint;

            printf("Pos joint=%d on %d degres\n", joint, degs);
            int rc = modbus_write_register(ctx, 4 + joint, degs);
            if (rc == -1) {
              fprintf(stderr, "%s\n", modbus_strerror(errno));
              return -1;
            }

            break;

        }
        break;

      default:
        printf("Message has not been process\n");
    }
    return(0);
  }

  void Proc()
  {
    uint16_t irs_raw[4];
    int rc, i;

    rc= modbus_read_registers(ctx, 0, 4, irs_raw);
    if (rc == -1) {
      fprintf(stderr, "%s\n", modbus_strerror(errno));
      return;
    }
    
    player_aio_data* data = new player_aio_data();
    data->voltages_count = 4;
    data->voltages = new float[4];

    for (i = 0; i < 4; i++) {
      data->voltages[i] = ((float)irs_raw[i]) / 0xffff * 5;
    }

    Publish(this->aio_addr, PLAYER_MSGTYPE_DATA, PLAYER_AIO_DATA_STATE, 
        (void*)data, sizeof(uint32_t) + 4 * sizeof(float));

    delete [] data->voltages;
    delete data;
  }

  virtual int MainSetup()
  {
    this->ctx = modbus_new_rtu(this->port, this->baud, 'N', 8, 1);
    modbus_set_slave(this->ctx, this->uid);
    if (modbus_connect(this->ctx) == -1) {
      fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
      return -1;
    }

    printf("Initialising modbus master on port=%s on speed=%d\n", this->port, this->baud);
    return(0);
  }


  virtual void Main()
  {
    for(;;) {
      pthread_testcancel();
      this->Proc();
      this->ProcessMessages(0);
      usleep(10000);
    }
  }

  virtual void MainQuit()
  {
    modbus_close(this->ctx);
    modbus_free(this->ctx);
    puts("Driver has been shutdown");
  }
};

// A factory creation function, declared outside of the class so that it
// can be invoked without any object context (alternatively, you can
// declare it static in the class).  In this function, we create and return
// (as a generic Driver*) a pointer to a new instance of this driver.
Driver* BotDriver_Init(ConfigFile* cf, int section)
{
  // Create and return a new instance of this driver
  return((Driver*)(new BotDriver(cf, section)));
}

// A driver registration function, again declared outside of the class so
// that it can be invoked without object context.  In this function, we add
// the driver into the given driver table, indicating which interface the
// driver can support and how to create a driver instance.
void BotDriver_Register(DriverTable* table)
{
  table->AddDriver("adventurebot", BotDriver_Init);
}

extern "C" {
  int player_driver_init(DriverTable* table)
  {
    BotDriver_Register(table);
    return(0);
  }
}
