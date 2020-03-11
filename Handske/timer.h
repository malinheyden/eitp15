/*
 * timer.h
 *
 * Created: 2020-03-10 15:40:43
 *  Author: ma5002he-s
 */ 
#include <avr/io.h>

/**
 * Initiates timer. Prescaler set to 1024. Overflow interrupt enabled
 */                                                                     
void timer0_init();