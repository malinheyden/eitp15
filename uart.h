/*
 * uart.h
 *
 * Created: 2020-02-26 14:41:22
 *  Author: ma5002he-s
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
void uart_init();

void uart_set_baudrate(int baudrate);
void uart_send_data(uint8_t data);
void uart_send_header();
void uart_send_tail()
void uart_enable_even_parity();
void uart_enable_odd_parity();
void uart_disable_parity();

#endif /* ADC_H_ */