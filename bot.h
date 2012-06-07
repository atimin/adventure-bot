#ifndef BOT_H
#define BOT_H

#include <inttypes.h>

#define SET(PORT, PIN) PORT |= _BV(PIN)
#define RESET(PORT, PIN) PORT &= ~_BV(PIN)

#define RF_LED            PORTD7 
#define LF_LED            PORTB0
#define LB_LED            PORTB4

#define TX                PORTD3  
#define RX                PORTB3  

typedef struct _bot_map_t {
    uint16_t ir1;
    uint16_t ir2;
    uint16_t ir3;
    uint16_t ir4;
} bot_map_t;

#endif
