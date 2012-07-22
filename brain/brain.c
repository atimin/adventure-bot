#include <stdio.h>
#include <math.h>
#include <libplayerc/playerc.h>

#define PAN  0
#define TITL 1

typedef struct bot_t 
{
  playerc_client_t *client;
  playerc_actarray_t *head;
  playerc_aio_t *irs;
} BOT; /* optional variable list */;

BOT* bot_create(const char* host, int port, int irs_index, int head_index)
{
  BOT* bot = malloc(sizeof(BOT)); 
  
  bot->client = playerc_client_create(NULL, host, port);
  bot->head = playerc_actarray_create(bot->client, irs_index);
  bot->irs = playerc_aio_create(bot->client, head_index);

  return bot;
}

int bot_connect(BOT *bot)
{
  if (playerc_client_connect(bot->client))
    return -1;
  playerc_client_datamode(bot->client, PLAYERC_DATAMODE_PULL);

  if (playerc_aio_subscribe(bot->irs, PLAYER_OPEN_MODE))
    return -1;

  if (playerc_actarray_subscribe(bot->head, PLAYER_OPEN_MODE))
    return -1;

  return 0;
}

void bot_delete(BOT* bot)
{
  playerc_aio_destroy(bot->irs);
  playerc_actarray_destroy(bot->head);
  playerc_client_destroy(bot->client);
}

void bot_disconnect(BOT* bot)
{
  playerc_aio_unsubscribe(bot->irs);
  playerc_actarray_unsubscribe(bot->head);
  playerc_client_disconnect(bot->client);
}

void bot_update(BOT *bot)
{
  playerc_client_read(bot->client);
}

void bot_turn_head(BOT *bot, float rads, int axis)
{
  playerc_actarray_position_cmd(bot->head, axis, rads);
}


#define POINTS     7 
#define OFFSET_DEG 10
#define BASE_DEG   60


int main(int argc, const char *argv[])
{
  int i,j;
  BOT *bot = bot_create("localhost", 6665, 0, 0);
  int deg_i, deg_j;

  if (!bot_connect(bot)) {

    for (i = 0; i < POINTS; i++) {
      for (j = 0; j < POINTS; j++) {
        bot_update(bot);
        deg_i = (BASE_DEG + OFFSET_DEG*i);
        deg_j = (BASE_DEG + OFFSET_DEG*j);
        bot_turn_head(bot, deg_i/57.32, PAN);
        bot_turn_head(bot, deg_j/57.32, TITL);
        printf("[%d,%d],[%.2f, %.2f, %.2f, %.2f]\n", deg_i, deg_j, 
            bot->irs->voltages[0],
            bot->irs->voltages[1],
            bot->irs->voltages[2],
            bot->irs->voltages[3]
        );
      }

      

      sleep(1);
    }

    bot_turn_head(bot, M_PI/2, TITL);
    bot_turn_head(bot, M_PI/2, PAN);

    sleep(1);
  }
  else
    fprintf(stderr, "Something wrong\n");


  bot_disconnect(bot);
  bot_delete(bot);

  return 0;
}
