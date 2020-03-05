/*
 * MalinTest.c
 *
 * Created: 2020-02-05 15:00:33
 * Author : ma5002he-s
 */ 
#include "main.h"

volatile uint8_t rx_data;

int main(void)
{
	
	init_leds();			//Configure leds as output
    
	x_y_mux_adc = 1;		//Set initial values
	uart_state = 1;
	
	adc_init();				// Initialize adc
	uart_init();			// Initialize uart

	sei();					// Enable interrupts globally
	adc_start();			// Start adc
	//uart_send_header();	// Send first header in uart
	
    while (1) {
		status_leds_x(&adc_value_x);
		status_leds_y(&adc_value_y);
		//_delay_ms(100);
		PORTB ^= (1 << LED_N_1);
    }
}

void status_leds_x(const uint16_t* adc_value)
{	
	//Turn off all leds, then turn on leds corresponding to adc_value (tilt)
	PORTB &=~ ((1 << LED_N_1)|(1 << LED_N_2)|(1 << LED_N_3));
	PORTD &=~ ((1 << LED_S_1)|(1 << LED_S_2)|(1 << LED_S_3));
	if(*adc_value > 581){
		PORTB |= (1 << LED_N_1)|(1 << LED_N_2)|(1 << LED_N_3);
	}
	else if (*adc_value > 553){
		PORTB |=(1 << LED_N_1)|(1 << LED_N_2);
		PORTB &=~ (1 << LED_N_3);
	}
	else if (*adc_value > 524){
		PORTB |=(1 << LED_N_1);
		PORTB &=~ ((1 << LED_N_2)|(1 << LED_N_3));
	}
	else if (*adc_value > 496){
		//do nothing, leds already cleared
	}
	else if (*adc_value > 467){
		PORTD |=(1 << LED_S_1);
		PORTD &=~ ((1 << LED_S_2)|(1 << LED_S_3));
	}
	else if (*adc_value > 439){
		PORTD |=(1 << LED_S_1)|(1 << LED_S_2);
		PORTD &=~ (1 << LED_S_3);
	}
	else{
		PORTD |=(1 << LED_S_1)|(1 << LED_S_2)|(1 << LED_S_3);
	}
}

void status_leds_y(const uint16_t* adc_value)
{
	
	PORTB &=~ ((1 << LED_W_1)|(1 << LED_W_2)|(1 << LED_W_3));
	PORTA &=~ ((1 << LED_E_1)|(1 << LED_E_2)|(1 << LED_E_3));
	if(*adc_value > 581){
		PORTB |= (1 << LED_W_1)|(1 << LED_W_2)|(1 << LED_W_3);
	}
	else if (*adc_value > 553){
		PORTB |=(1 << LED_W_1)|(1 << LED_W_2);
		PORTB &=~ (1 << LED_W_3);
	}
	else if (*adc_value > 524){
		PORTB |=(1 << LED_W_1);
		PORTB &=~ ((1 << LED_W_2)|(1 << LED_W_3));
	}
	else if (*adc_value > 496){
		//do nothing, leds already cleared
	}
	else if (*adc_value > 467){
		PORTA |=(1 << LED_E_1);
		PORTA &=~ ((1 << LED_E_2)|(1 << LED_E_3));
	}
	else if (*adc_value > 439){
		PORTA |=(1 << LED_E_1)|(1 << LED_E_2);
		PORTA &=~ (1 << LED_E_3);
	}
	else{
		PORTA |=(1 << LED_E_1)|(1 << LED_E_2)|(1 << LED_E_3);
	}
}

void init_leds()
{
	DDRA |= (1<<LED_E_1)|(1<<LED_E_2)|(1<<LED_E_3);
    DDRB |= (1<<LED_N_1)|(1<<LED_N_2)|(1<<LED_N_3)|(1<<LED_W_1)|(1<<LED_W_2)|(1<<LED_W_3);
	DDRD |= (1<<LED_S_1)|(1<<LED_S_2)|(1<<LED_S_3); 	
}

ISR(ADC_vect)
{
	if(x_y_mux_adc == 0){
		adc_value_y = ADC;
	}else{
		adc_value_x = ADC;
	}
	adc_change_pin(x_y_mux_adc);
	x_y_mux_adc ^= (0b00000001);
	adc_start();

}

//Interrupt executes when last transmission is completed. Puts the next frame in tx buffer
ISR(USART0_TX_vect)
{
	//switch (uart_state){
		//case 0:
			////send header
			//uart_send_header();
			//uart_state++;
		//break;
		//case 1:
			////send data
			//uart_send_data(uart_value);
			//uart_state++;
		//break;
		//case 2:
			////Send tail
			//uart_send_tail();
			//uart_state = 0;
		//break;
	//}
}

ISR(USART0_RX_vect)
{
	rx_data = UDR0;
	UDR0 = rx_data;
}
