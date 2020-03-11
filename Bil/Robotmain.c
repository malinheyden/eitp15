    /*
	//  * BrumbrumRobot.c
	//  *
	//  * Created: 2020-02-25 12:51:42
	//  * Author : elt14iob
	//  */ 
	// 
	// #define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "robot.h"
#include "timer.h"
#include "uart.h"

//Interrupt Variables for timer 1 & 3
//Counter is used to not updated speed to often
volatile uint8_t timer1_cnt;
volatile uint8_t timer3_cnt;
//Period is used to set and change specific speed of each motor
volatile uint8_t period1 = 60;
volatile uint8_t period3 = 60;
//Set direction of motors
volatile uint8_t direction1 = 0;
volatile uint8_t direction3 = 0;


//Interrupt Variables for UART_RX
volatile uint8_t rx_data_x = 0;
volatile uint8_t rx_data_y = 0;
volatile uint8_t rx_counter = 0;
volatile uint8_t rx_reader = 0;
volatile uint8_t rx_flag_new_data = 0; 
	 
int main(void){
	
	timer_init();
	timer1_set_prescaler(PRESCALER_256);
	timer1_set_period(60);
	
	timer3_set_prescaler(PRESCALER_256);
	timer3_set_period(60);
	
	uart_init();
	
	//Set pins output for Drivers MODE Signal
	DDRA |= (1 << STEP1_MODE0) | (1 << STEP1_MODE1) | (1 << STEP1_MODE2) | (1 << STEP2_MODE0) | (1 << STEP2_MODE1) | (1 << STEP2_MODE2);
	
	//Reset Drivers MODE Signal
	PORTA &=~ (1 << STEP1_MODE0) | (1 << STEP1_MODE1) | (1 << STEP1_MODE2) | (1 << STEP2_MODE0) | (1 << STEP2_MODE1) | (1 << STEP2_MODE2);
	
	//Set Drivers MODE Signal, step size
	PORTA |= MICRO_STEP1_8;
	PORTA |= MICRO_STEP2_8;
	

	//Set pins output for Drivers DIR Signal
	DDRC |= (1 << STEP1_DIR) | (1 << STEP2_DIR);
	
	//Reset Drivers DIR Signal
	PORTC &=~ (1 << STEP1_DIR) | (1 << STEP2_DIR);
	
	sei(); // Enable global interrupt, cli() to disable
	
    while (1){	
		if (rx_flag_new_data == 1){
			driver_speed(rx_data_x, &period1, &period3);
			driver_direction(rx_data_y, &direction1, &direction3);
			rx_flag_new_data = 0;
		}
	}
	

	
}
	 /**
	 * Interrupt when TIMER1 PMW gets overflow, then we can change the period.
	 * This is to avoid the PMW getting 1second restart time.
	 *
	 */
	 ISR(TIMER1_OVF_vect) {
	 		timer1_set_period(period1 + direction1);
	 }
	 
	 /**
	 * Interrupt when TIMER3 PMW gets overflow, then we can change the period.
	 * This is to avoid the PMW getting 1second restart time.   
	 *
	 */
	 ISR(TIMER3_OVF_vect) {
	 		timer3_set_period(period3 + direction3);
	 }
	 
	 /**
	 *UART
	 *
	 */
	 ISR(USART0_RX_vect) {
	 	uint8_t rx_temp_data = UDR0;
	 		
	 	if(rx_temp_data == RX_HEADER){	
	 		rx_counter++;
	 	} else if (rx_counter == 1){
	 		rx_data_x = rx_temp_data;
	 		rx_counter++;
	 	} else if (rx_counter == 2 && rx_temp_data != RX_TAIL){
	 		rx_data_y = rx_temp_data;
	 		rx_counter++;
	 	} else if(rx_counter == 3 && rx_temp_data == RX_TAIL){
	 		rx_flag_new_data = 1;
	 		rx_counter = 0;
	 	} else{
	 		rx_data_x = 0;
	 		rx_counter = 0;
	 		rx_temp_data = 0;
	 	}
		 if(rx_flag_new_data == 1){
		 rx_flag_new_data = 1;
		 }
	 	
	 }
	 	
	
	
	/*
 * testmain.c
 *
 * Created: 2020-03-10 14:16:37
 *  Author: elt14iob
 */ 

// 
// #define F_CPU 16000000UL
// #include <avr/io.h>
// #include <util/delay.h>
// #include <avr/interrupt.h>
// #include "robot.h"
// #include "timer.h"
// #include "uart.h"
// 
// volatile uint8_t period3 = 60;
// 
// int main()
// {
// 	timer_init();
// 	//timer1_set_prescaler(PRESCALER_256);
// 	//timer1_set_period(60);
// 	
// 	timer3_set_prescaler(PRESCALER_256);
// 	timer3_set_period(60);
// 	
// 	DDRA |= (1 << STEP1_MODE0) | (1 << STEP1_MODE1) | (1 << STEP1_MODE2) | (1 << STEP2_MODE0) | (1 << STEP2_MODE1) | (1 << STEP2_MODE2);
// 	PORTA |= MICRO_STEP1_8;
// 	PORTA |= MICRO_STEP2_8;
// 	DDRC |= (1 << STEP1_DIR) | (1 << STEP2_DIR);
// 	
// 	sei();
// 	
// 	while (1){
// 		period3 = 90;
// 		_delay_ms(5000);
// 		period3 = 60;
// 		_delay_ms(5000);
// 		period3 = 20;
// 		_delay_ms(5000);
// 		period3 = 90;
// 		_delay_ms(5000);
// 	}
// }
// 
// ISR(TIMER3_OVF_vect) {
// 		timer3_set_period(period3);
// }