/*
 * timer.h
 *
 * Created: 2020-02-25 17:34:45
 *  Author: elt14iob
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>


/**< Define prescaler sizes */
#define PRESCALER_STOP  0 
#define PRESCALER_1		1
#define PRESCALER_8		2
#define PRESCALER_64	3
#define PRESCALER_256   4
#define PRESCALER_1024  5

/**
 * Initiate timer by, 
 * set output for Driver Step signal, 
 * clears registers TCCRnA,
 * defines Fast in PMW TCCRnA, TCCRnB
 */
void timer_init(void);

/**
 * Reset Clock Select Bit Description and sets prescaler for PMW in TCCR1B. 
 *
 * @param prescaler Defines the prescaler of the PMW to divide the clock speed.
 */
void timer1_set_prescaler(uint8_t prescaler);

/**
 * Set counter(height) of the PMW in ICR1 and duty cycle 50% in OCR1A
 *
 * @param period Period time of PMW
 */
void timer1_set_period(uint8_t period);

/**
 * Reset Clock Select Bit Description and sets prescaler for PMW in TCCR3B. 
 *
 * @param prescaler Defines the prescaler of the PMW to divide the clock speed.
 */
void timer3_set_prescaler(uint8_t prescaler);

/**
 * Set counter(height) of the PMW in ICR3 and duty cycle 50% in OCR3A
 *
 * @param period Period time of PMW
 */
void timer3_set_period(uint16_t period);

#endif /* TIMER_H_ */