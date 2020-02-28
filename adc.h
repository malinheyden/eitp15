/*
 * adc.h
 *
 * Created: 2020-02-21 17:30:38
 *  Author: ma5002he-s
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adc_init();
void adc_start();
void adc_change_pin();


#endif /* ADC_H_ */