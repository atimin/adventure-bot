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
  
  sp = serial_create();
  serial_config(sp, BAUD_9600, &PORTB, RX, &PORTD, TX);
  serial_debug(sp, &PORTD, RF_LED);
}

int main()
{
  init();
  char* msg = "Hello, World!!!\n";
  for(;;) {
    for(int i=0; i < 80; ++i,  _delay_loop_2(50000));
    serial_write_bytes(sp, (uint8_t*)msg, 16);
  }
}
