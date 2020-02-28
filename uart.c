/*
 * uart.c
 *
 * Created: 2020-02-26 14:41:12
 *  Author: ma5002he-s
 */ 
#include "uart.h"

void uart_init(){
	//Vad ska vi ha för baudrate? UBBRn 12 bitars reg, ekvation på sidan 240'
	//Vad har xbee för baudrate?
	//SET baud
	// set frame
	//enable tx or rx
	//For interrupt driven also clear global interrupt flag
	
	
	
	//Asynchronous is default
	//Set baud rate, high and low bits
	//UBRR0H |= 
	//UBRR0L |=
	
	//Enable transmitter
	UCSR0B |= (1<<TXEN0);
	
	//set frame format: 8 bits of data, no parity right now
	UCSR0B |= (1<<UCSZ00)|(1<<UCSZ01);
	
	//Enable TX
}

void uart_send_data(uint8_t data){
	
}

void uart_set_baudrate(int baudrate){
	//UBRR0H = 
}

void uart_enable_even_parity(){
	//Clear parity bits
	UCSR0C &=~((1<<UPM00)|(1<<UPM01));
	//Set parity bits for even parity
	UCSR0C |= (1<<UPM00);
}

void uart_enable_odd_parity(){
	//Clear parity bits
	UCSR0C &=~((1 << UPM00)|(1<<UPM01));
	//Set parity bits for even parity
	UCSR0C |= (1<<UPM00)|(1<<UPM01);
}

void uart_disable_parity(){
	//Clear parity bits
	UCSR0C &=~((1<<UPM00)|(1<<UPM01));	
}