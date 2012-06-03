#ifndef BOT_H
#define BOT_H


#define SET(PORT, PIN) PORT |= _BV(PIN)
#define RESET(PORT, PIN) PORT &= ~_BV(PIN)

#define RF_LED            PORTD7 
#define LF_LED            PORTB0

#define TX                PORTD3  
#define RX                PORTB3  

#endif
