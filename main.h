
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

//Define macros, vector v, mask m
//not used
#define bit_get(v,m) ((v) & (m))
#define bit_set(v,m) ((v) |= (m))
#define bit_clear(v,m) ((v) &= ~(m))
#define bit_flip(v,m) ((v) ^= (m))
#define BIT(x) (0x01 << (x))

// Define leds East, North, West, South

//PA
//1 = green, 2 = orange, 3 = red
#define LED_E_1 4
#define LED_E_2 5
#define LED_E_3 6
//PB
#define LED_N_1 4
#define LED_N_2 3
#define LED_N_3 2
//PB
#define LED_W_1 5
#define LED_W_2 6
#define LED_W_3 7
//PD
#define LED_S_1 3
#define LED_S_2 4
#define LED_S_3 5

//define X, Y, Z from accelerometer
//PA
#define X_ACC 0
#define Y_ACC 1
#define Z_ACC 2

volatile uint16_t adc_value_x;
volatile uint16_t adc_value_y;
volatile uint8_t x_y_mux_adc;
volatile uint8_t uart_value;

uint8_t uart_state; //*< Indicates for the uart to send header, data, or tail next.

void status_leds_x(const uint16_t* adc_value);
void status_leds_y(const uint16_t* adc_value);
void init_leds();

#endif