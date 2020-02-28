/*
 * MalinTest.c
 *
 * Created: 2020-02-05 15:00:33
 * Author : ma5002he-s
 */ 
#define F_CPU 16000000UL //for debugging
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "uart.h"

//Define macros, vector v, mask m
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

volatile uint16_t adc_value;
volatile uint8_t x_flag;

int main(void)
{
	//Configure leds as output
    DDRA |= (1<<LED_E_1)|(1<<LED_E_2)|(1<<LED_E_3);
    DDRB |= (1<<LED_N_1)|(1<<LED_N_2)|(1<<LED_N_3)|(1<<LED_W_1)|(1<<LED_W_2)|(1<<LED_W_3);
	DDRD |= (1<<LED_S_1)|(1<<LED_S_2)|(1<<LED_S_3); 

	//Start adc and enable interrupts
	adc_init();
	sei();
	adc_start();

    while (1) {
		//TODO kör kontinuerligt x sen y sen x i adc, sätt en flagga när omvandlingen är klar. Då körs en ifsats som tänder/släcker lampor

		PORTB &=~ ((1 << LED_N_1)|(1 << LED_N_2)|(1 << LED_N_3));
		PORTD &=~ ((1 << LED_S_1)|(1 << LED_S_2)|(1 << LED_S_3));
		if(adc_value > 581){
			PORTB |= (1 << LED_N_1)|(1 << LED_N_2)|(1 << LED_N_3);
		}
		else if (adc_value > 553){
			PORTB |=(1 << LED_N_1)|(1 << LED_N_2);
			PORTB &=~ (1 << LED_N_3);
		}
		else if (adc_value > 524){
			PORTB |=(1 << LED_N_1);
			PORTB &=~ ((1 << LED_N_2)|(1 << LED_N_3));
		}
		else if (adc_value > 496){
		//do nothing, leds already cleared
		}
		else if (adc_value > 467){
			PORTD |=(1 << LED_S_1);
			PORTD &=~ ((1 << LED_S_2)|(1 << LED_S_3));
		}
		else if (adc_value > 439){
			PORTD |=(1 << LED_S_1)|(1 << LED_S_2);
			PORTD &=~ (1 << LED_S_3);
		}
		else{
			PORTD |=(1 << LED_S_1)|(1 << LED_S_2)|(1 << LED_S_3);
		}
    }
}


ISR(ADC_vect)
{

	adc_value = ADC;
	//adc_change_pin();
	adc_start();

}

//Interrupt executes when last transmission is completed. Puts the next frame in tx buffer
ISR(USART1_TX_vect)
{
	//Data can only be written to buffer if UDRE flag is set
	if ((UCSR0A & (1 << UDRE0)) == (1 << UDRE0)){
		uart_send_data();
	}
	
}
