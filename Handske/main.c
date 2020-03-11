/*
 * MalinTest.c
 *
 * Created: 2020-02-05 15:00:33
 * Author : ma5002he-s
 */ 
#include "main.h"



int main()
{
	
	init_leds();			//Configure leds as output
    
	x_y_mux_adc = 1;		//Set initial values
	uart_state = 0;
	
	adc_init();				// Initialize adc
	uart_init();			// Initialize uart
	timer0_init();

	sei();					// Enable interrupts globally
	adc_start();			// Start adc
	
    while (1) {
		status_leds_x(&adc_mean_x);
		status_leds_y(&adc_mean_y);
		calculate_uart_x();
		calculate_uart_y();
		
    }
}

void calculate_uart_x()
{
	//Shift down adc value by 2 to fit in 8 bits
	uart_x = (adc_mean_x >> 2);
	if(uart_x == 0xFF){
		uart_x--;
	}
	if (uart_x == 0xFE){
		uart_x--;
	}
}

void calculate_uart_y()
{
	uart_y = (adc_mean_y >> 2);
	if(uart_y == 0xFF){
		uart_y--;
	}
	if (uart_y == 0xFE){
		uart_y--;
	}
}

void status_leds_x(const uint16_t* adc_value)
{	
	//Turn off all leds, then turn on leds corresponding to adc_value (tilt)
	PORTB &=~ ((1 << LED_N_1)|(1 << LED_N_2)|(1 << LED_N_3));
	PORTD &=~ ((1 << LED_S_1)|(1 << LED_S_2)|(1 << LED_S_3));
	if(*adc_value > 581){
		PORTB |= (1 << LED_N_1)|(1 << LED_N_2)|(1 << LED_N_3);
	} else if (*adc_value > 553){
		PORTB |=(1 << LED_N_1)|(1 << LED_N_2);
		PORTB &=~ (1 << LED_N_3);
	} else if (*adc_value > 524){
		PORTB |=(1 << LED_N_1);
		PORTB &=~ ((1 << LED_N_2)|(1 << LED_N_3));
	} else if (*adc_value > 496){
		//do nothing, leds already cleared
	} else if (*adc_value > 467){
		PORTD |=(1 << LED_S_1);
		PORTD &=~ ((1 << LED_S_2)|(1 << LED_S_3));
	} else if (*adc_value > 439){
		PORTD |=(1 << LED_S_1)|(1 << LED_S_2);
		PORTD &=~ (1 << LED_S_3);
	} else{
		PORTD |=(1 << LED_S_1)|(1 << LED_S_2)|(1 << LED_S_3);
	}
}

void status_leds_y(const uint16_t* adc_value)
{
	//Turn of leds
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

//Reads 8 values of X and Y, then creates the mean of these. Triggers uart send
ISR(ADC_vect)
{
	if(adc_counter < 16){
		if(x_y_mux_adc == 0){
			//adc_value_y = ADC;
			adc_y_sum += ADC;
		}else{
			//adc_value_x = ADC;
			adc_x_sum += ADC;
		}
		adc_change_pin(x_y_mux_adc);
		x_y_mux_adc ^= (0b00000001);
		adc_start();
		adc_counter++;
	}else if(adc_counter == 16){
		uart_flag = 1;
		adc_mean_x = (adc_x_sum >> 3);	//Take the mean, divide by 8
		adc_mean_y = (adc_y_sum >> 3);
		uart_send_header();
		adc_counter++;
	}else{
		adc_counter = 0;
		adc_y_sum = 0;
		adc_x_sum = 0;
	}
}

//Interrupt executes when last transmission is completed. 
//Puts the next frame in tx buffer if uart_flag is set
ISR(USART0_TX_vect)
{
	if(uart_flag == 1){
		switch (uart_state){
		case 0:
			//send data
			uart_send_data(uart_x);
			uart_state++;
			break;
		case 1:
			//send data
			uart_send_data(uart_y);
			uart_state++;
		break;
		case 2:
		//Send tail
			uart_send_tail();
			uart_state = 0;
			uart_flag = 0;
			break;
		}
	}
	
}

ISR(USART0_RX_vect)
{
	rx_data = UDR0;
	UDR0 = rx_data;
}

//This method starts the adc after 6 timer cycles ~ 100 ms
ISR(TIMER0_OVF_vect)
{
	timer_counter++;
	if (timer_counter == 6){
		timer_counter = 0;
		adc_start();
	}
}
