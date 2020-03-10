/*
 * adc.h
 *
 * Created: 2020-02-21 17:30:38
 *  Author: ma5002he-s
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

/**
 * Initializes the analog to digital converter. Sets voltage reference to AVCC pin,
 * enables interrupt, and sets prescaler to fit a 16MHz clock frequency. By default
 * adc start on pin 0.                                                                   
 */
void adc_init();

/**
 * Starts thead conversion.                                                                
 */
void adc_start();

/**
 * Changes the pin that is input to adc. Must be smaller than 31.
 * @param MUX_SEL value that selects between pins in the port.
 */
void adc_change_pin(uint8_t MUX_SEL);


#endif /* ADC_H_ */