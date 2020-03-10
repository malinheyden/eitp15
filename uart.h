/*
 * uart.h
 *
 * Created: 2020-02-26 14:41:22
 *  Author: ma5002he-s
 */ 

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define HEADER 0xFF //*< UART header
#define TAIL 0xFE   //*< UART tail


/**
 * Initializes UART 0 in asynchronous mode with baud rate 9600.
 * Enables transmitter and TX complete interrupt
 * Frame format is 8 data bits, 1 stop bit, no parity bit.
 */
void uart_init();

/**
 * Sends the specified data on the UART when the buffer is empty.
 * @param data the data to be sent
 */
void uart_send_data(uint8_t data);

/**
 * Sends the specified header on the UART when the buffer is empty.
 */
void uart_send_header();

/**
 * Sends the specified tail on the UART when the buffer is empty.
 */
void uart_send_tail();

/**
 * Enables parity bit, even
 */
void uart_enable_even_parity();

/**
 * Enables parity bit, odd
 */
void uart_enable_odd_parity();

/**
 * Disables parity bit
 */
void uart_disable_parity();

#endif /* ADC_H_ */