
/*
 * main.h
 *
 * Created: 2020-03-04 16:28:50
 *  Author: ma5002he-s
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL //for debugging
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "uart.h"
#include "timer.h"

// Define leds East, North, West, South
//PA
//1 = green, 2 = orange, 3 = red
#define LED_E_1 4	// LED East, green
#define LED_E_2 5	// LED East, orange
#define LED_E_3 6	// LED East, red
//PB			  	 
#define LED_N_1 4	// LED North, green
#define LED_N_2 3	// LED North, orange
#define LED_N_3 2	// LED North, red
//PB			  	
#define LED_W_1 5	// LED West, green
#define LED_W_2 6	// LED West, orange
#define LED_W_3 7	// LED West, red
//PD			  
#define LED_S_1 3	// LED South, green
#define LED_S_2 4	// LED South,	orange
#define LED_S_3 5	// LED South,	red

//define X, Y, Z from accelerometer
//PA
#define X_ACC 0		// pin with X-value from accelerometer
#define Y_ACC 1		// pin with Y-value from accelerometer
#define Z_ACC 2		// pin with Z-value from accelerometer
		

uint16_t adc_mean_x;				//The mean value of X from accelerometer
uint16_t adc_mean_y;				//The mean value of Y from accelerometer
uint8_t x_y_mux_adc;				//Flag for keeping track of X and Y
uint8_t uart_x;						//X-value to be sent on UART
uint8_t uart_y;						//Y-value to be sent on UART
uint8_t uart_state;					//Indicates for the uart to send header, data, or tail next.
volatile uint8_t rx_data;			//Data recieved on the uart
volatile uint8_t timer_counter;		//Counter for timer
volatile uint8_t adc_counter;		//Counter for adc
volatile uint16_t adc_x_sum;		//Accumulated sum of x values
volatile uint16_t adc_y_sum;		//Accumulated sum of x values
volatile uint8_t uart_flag = 0;		//Flag for when to send on uart


/**
 * Lights the leds in x direction showing the tilt
 * @param adc_value the digital value for x-direction
 */
void status_leds_x(const uint16_t* adc_value);

/**
 * Lights the leds in x direction showing the tilt
 * @param adc_value the digital value for y-direction
 */
void status_leds_y(const uint16_t* adc_value);

/**
 * Calculates X value to send on uart by downshifting adc value by 2
 */
void calculate_uart_x();

/**
 * Calculates Y value to send on uart by downshifting adc value by 2
 */
void calculate_uart_y();

/**
 * Configures leds as outputs
 */
void init_leds();

#endif