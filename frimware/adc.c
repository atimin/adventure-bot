#include "adc.h"

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
