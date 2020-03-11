/*
 * uart.c
 *
 * Created: 2020-02-26 14:41:12
 *  Author: ma5002he-s
 */ 
#include "uart.h"

void uart_init()
{	
	//Asynchronous is default
	//Set baud rate, (high) and low bits
	//Default baud rate 9600 -> UBRR0L = 103 
	UBRR0L |= 103 ;
	
	//Enable tx complete interrupt, enable transmitter
	UCSR0B |= (1 << TXCIE0)|(1 << TXEN0)|(1 << RXEN0)|(1 << RXCIE0);
	
	//set frame format: 8 bits of data, no parity, 1 stop bit.
	UCSR0C |= (1 << UCSZ00)|(1 << UCSZ01);
	
}

void uart_send_data(uint8_t data)
{
	//Wait for buffer to be empty
	while(!(UCSR0A & (1 << UDRE0))){
		
	}
	UDR0 = data;
}

void uart_send_header()
{	
	//Wait for buffer to be empty
	while(!(UCSR0A & (1 << UDRE0))){
		
	}
	UDR0 = HEADER;
}

void uart_send_tail()
{
	//Wait for buffer to be empty
	while(!(UCSR0A & (1 << UDRE0))){
		
	}
	UDR0 = TAIL;
}



void uart_enable_even_parity()
{
	//Clear parity bits
	UCSR0C &=~((1<<UPM00)|(1<<UPM01));
	//Set parity bits for even parity
	UCSR0C |= (1<<UPM00);
}

void uart_enable_odd_parity()
{
	//Clear parity bits
	UCSR0C &=~((1 << UPM00)|(1<<UPM01));
	//Set parity bits for odd parity
	UCSR0C |= (1<<UPM00)|(1<<UPM01);
}

void uart_disable_parity()
{
	//Clear parity bits
	UCSR0C &=~((1<<UPM00)|(1<<UPM01));	
}