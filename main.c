#include "bot.h"

#include "serial.h"
#include "modbus_rtu.h"

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay_basic.h>
#include <string.h>

#define SLAVE_ID 1

static serial_t *sp;
static mb_rtu_t *mb;
static bot_map_t *map;

ISR (TIMER2_OVF_vect)
{
  mb_rtu_proc(mb, (uint16_t*)map, sizeof(*map)/2);

  TCCR2B = 0x00;        /* Stop timer2 */ 


  RESET(PORTB, LB_LED);

}

ISR (PCINT0_vect)
{
  serial_handle(sp);    /* Receive byte */

  TCNT2 = 0;            /* Reset a timeout for ADU package */
  TCCR2B = 0x07;        /* Run timer2 */ 
}

void measure_irs(bot_map_t *map)
{
  uint16_t smp[4] = { 0x0, 0x0, 0x0, 0x0 }; 

  for (uint8_t i = 0; i < 4; i++) {
    ADMUX = (ADMUX & 0xf0) | (IR_LEFT + i);
    SET(ADCSRA, ADSC);

    while(ADCSRA & _BV(ADSC))
      continue;

    smp[i] = ADCL;
    smp[i] += (uint16_t)ADCH << 8;
  }

  memcpy(map, smp, 4 * sizeof(*smp));
}

void init()
{
  /* Init outputs for I/O ports */
  DDRD = _BV(RF_LED) | _BV(TX) | _BV(IR_LED);
  DDRB = _BV(LF_LED) | _BV(LB_LED);
  SET(PORTD, IR_LED);

  /* Init interrupt for RX */
  SET(PCICR, PCIE0);
  SET(PCMSK0, PCINT3);
  
  /* Init software serial port */
  sp = serial_create();
  serial_config(sp, BAUD_9600, &PINB, RX, &PORTD, TX);
  serial_debug(sp, &PORTD, RF_LED, &PORTB, LF_LED);

  /* Init modbus slave */
  mb = mb_rtu_create();
  mb_rtu_config(mb, SLAVE_ID, sp);

  /* Init map */
  map = malloc(sizeof(*map));

  /* Turn on a interrupt for timer2. Seek an end of ADU package.*/
  TIMSK2 |= _BV(TOIE2);  

  /* Init ADC Vref = Vcc, left align result off conversion */ 
  ADMUX =  _BV(ADLAR) | _BV(REFS0);
  ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);

  sei();
}

int main()
{
  init();
  for(;;) {
    measure_irs(map);
  }
} 
