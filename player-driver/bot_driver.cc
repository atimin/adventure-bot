/*
 * Driver for the Player server.
 * 2012 Aleksey Timin
 *
 * Public Domain
 * */

#include <libplayercore/playercore.h>

class BotDriver : public ThreadedDriver {
public:
  BotDriver(ConfigFile* cf, int section);

private:
  /* data */
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
  table->AddDriver("botdriver", BotDriver_Init);
}

