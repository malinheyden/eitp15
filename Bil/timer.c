/*
 * timer.c
 *
 * Created: 2020-02-25 17:34:29
 *  Author: elt14iob
 */ 

#include "timer.h"
#include "robot.h"


void timer_init(){
	
	//Set STEPn_STEP pin as output
	DDRD   |= (1 << STEP1_STEP);
	DDRB   |= (1 << STEP2_STEP);
	
	//Clear OCnA/OCnB on Compare Match (Set output to low level). 
	TCCR1A |= (1 << COM1A1);
	TCCR3A |= (1 << COM3A1);
	
	//Define Fast PWM in WGMn3-n0 = 1110
	TCCR1A |= (1 << WGM11);
	TCCR3A |= (1 << WGM31);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR3B |= (1 << WGM32) | (1 << WGM33);
	
	// Aktiverar något.. :)
	TIMSK3 |= (1 << TOIE3);
	TIMSK1 |= (1 << TOIE1);
}

void timer1_set_prescaler(uint8_t prescaler) {
	
	//Reset Clock Select Bit Description 
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
	
	//Chooses prescaler, a.k.a clock speed.
	TCCR1B |= prescaler;
	
}

void timer1_set_period(uint8_t period) {
	
	//Height of PMW, higher value = longer period (Saw-tooth-Wave)
	ICR1 = (0x00 << 8) | period;
	
	//Shift 1 bit = divide by 2 = 50% Duty cycle
	OCR1A = ((0x00 << 8) | period) >> 1;
	
}

void timer3_set_prescaler(uint8_t prescaler) {
	
	//Reset Clock Select Bit Description
	TCCR3B &= ~((1 << CS32) | (1 << CS31) | (1 << CS30));
	
	//Chooses prescaler, a.k.a clock speed.
	TCCR3B |= prescaler;
	
}

void timer3_set_period(uint16_t period) {
	
	//Height of PMW, higher value = longer period (Saw-tooth-Wave)
	ICR3 = period;
	
	//Shift 1 bit = divide by 2 = 50% Duty cycle
	OCR3A = period >> 1;
	
}