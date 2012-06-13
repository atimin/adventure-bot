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

#define IR_LEFT           4
#define IR_RIGH           5
#define IR_TOP            6
#define IR_BOTTOM         7

#define IR_LED            PORTD2

typedef struct _bot_map_t {
    uint16_t ir_left;
    uint16_t ir_right;
    uint16_t ir_top;
    uint16_t ir_bottom;
} bot_map_t;

#endif
