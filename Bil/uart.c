/*
 * uart.c
 *
 * Created: 2020-03-04 16:55:45
 *  Author: elt14iob
 */ 

#include "uart.h"

void uart_init(){
	
	/* Set baud rate */
	UBRR0L = BAUD;
	/* Enable receiver (for transmitter => |(1<<TXEN0) */
	UCSR0C |= (1<<RXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C |= (1<<USBS0)|(3<<UCSZ00);
	//Enable receive interrupt and override normal port operation.
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0);
	
}