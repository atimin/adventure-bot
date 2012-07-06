/*
 * ADC conversation. 
 * 2012 Aleksey Timin
 *
 * Public Domain
 * */


#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <inttypes.h>

extern uint16_t adc_convert(uint8_t channel);

#endif
