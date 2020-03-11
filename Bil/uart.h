/*
 * uart.h
 *
 * Created: 2020-03-04 16:56:06
 *  Author: elt14iob
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

//#define BAUD_RATE 9600	
#define BAUD 103

//Interrupt Variables for UART_RX
#define RX_HEADER	(0xff)
#define RX_TAIL		(0xfe)

/** 
*	USART initialization, 
*   receive interrupt enable,
*	with Asynchronous - UART
*	and baud rate = 0
*/
void uart_init(void);


/**	
*	USART Receive function,
*	
*/
unsigned char USART_Receive(void);
	 


#endif /* UART_H_ */