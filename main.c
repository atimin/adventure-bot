#include "bot.h"
#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay_basic.h>

static serial_t* sp;

ISR (PCINT0_vect)
{
  serial_handle(sp);
}

void init()
{
  DDRD = (1 << RF_LED) | (1 << TX);
  DDRB = (1 << LF_LED);

  /* Init interrupt for RX */
  SET(SREG, 7);
  SET(PCICR, PCIE0);
  SET(PCMSK0, PCINT3);
  
  /* Init software serial port */
  sp = serial_create();
  serial_config(sp, BAUD_9600, &PINB, RX, &PORTD, TX);
  serial_debug(sp, &PORTD, RF_LED);
}

int main()
{
  init();
  for(;;) {
    for(int i=0; i < 80; ++i,  _delay_loop_2(50000));
      uint8_t recive[5];
      int c = serial_read_bytes(sp, recive, 5);
      if (c > 0 )
        serial_write_bytes(sp, recive, c);
  }
} 
