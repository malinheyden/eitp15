/*
 * timer.c
 *
 * Created: 2020-03-10 15:34:52
 *  Author: ma5002he-s
 */ 

#include "timer.h"
void timer0_init()
{
	//Set prescaler 64
	TCCR0B |= (1 << CS02)|(1 << CS00);
	//Overflow interrupt enable
	TIMSK0 |= (1 << TOIE0);
}
