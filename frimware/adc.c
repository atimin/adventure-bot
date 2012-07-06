#include "adc.h"

void init_adc()
{
  /* Init ADC Vref = Vcc, left align result off conversion */ 
  ADMUX =  _BV(ADLAR) | _BV(REFS0);
  ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
}

uint16_t adc_convert(uint8_t channel) {
  uint16_t result; 

  ADMUX = (ADMUX & 0xf0) | (channel);
  ADCSRA |= _BV(ADSC);

  while(ADCSRA & _BV(ADSC))
    continue;

  result = ADCL;
  result += (uint16_t)ADCH << 8;
  return result;
}
