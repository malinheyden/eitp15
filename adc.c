/*
 * adc.c
 *
 * Created: 2020-02-21 17:30:27
 *  Author: ma5002he-s
 */ 

#include "adc.h"


void adc_init()
{
	// Set adc reference to AVCC pin	
	ADMUX  |= (1 << REFS0);
	// Enables adc, enable interrupt and set prescaler to 128 => adc clock 125kHz
	ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
	
}

void adc_start() {
	
	// Start conversion by setting ADSC bit high
	ADCSRA |= (1 << ADSC);
	
}

//Send in int to which pin to change to
void adc_change_pin(uint8_t MUX_SEL) {
		ADMUX &= ~((1 << MUX0)|(1 << MUX1));
		ADMUX |= MUX_SEL;
}
