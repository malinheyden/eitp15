/*
 * timer.c
 *
 * Created: 2020-03-09 08:54:29
 *  Author: elt14iob
 */ 

#include "robot.h"
#include "timer.h"

void driver_direction(uint8_t rx_data, uint8_t *direction1, uint8_t *direction3){
	cli();
	if (rx_data > DIRECTION_RIGHT_3){		
			*direction1 = 9; 
			*direction3 = -9; 					
		} else if (rx_data > DIRECTION_RIGHT_2){		
			*direction1 = 6;
			*direction3 = -6; 
		} else if (rx_data > DIRECTION_RIGHT_1){		
			*direction1 = 3;
			*direction3 = -3; 
		} else if (rx_data > SPEED_NEUTRAL){	
			*direction1 = 0;			
			*direction3 = 0;										
		} else if (rx_data > DIRECTION_LEFT_1){						
			*direction3 = 3;
			*direction1 = -3;
		} else if (rx_data > DIRECTION_LEFT_2){				
			*direction3 = 6;
			*direction1 = -6;
		} else if (rx_data > DIRECTION_LEFT_3){	
			*direction3 = 9;
			*direction1 = -9;
	}
	sei();
}

void driver_speed(uint8_t rx_data, uint8_t *period1, uint8_t *period3){
	cli();
	timer1_set_prescaler(PRESCALER_256);										/* Set prescaler in case it was stopped */
	timer3_set_prescaler(PRESCALER_256);										
	
	if(rx_data > SPEED_3){
		PORTC &=~ (1 << STEP1_DIR) | (1 << STEP2_DIR);
		*period1 = PERIOD_3;													
		*period3 = PERIOD_3;
	}else if(rx_data > SPEED_2){
		PORTC &=~ ((1 << STEP1_DIR) | (1 << STEP2_DIR));
		*period1 = PERIOD_2;													
		*period3 = PERIOD_2;
	}else if(rx_data > SPEED_1){
		PORTC &=~ ((1 << STEP1_DIR) | (1 << STEP2_DIR));
		*period1 = PERIOD_1;													/* Change period1 to new period that gives desired speed */
		*period3 = PERIOD_1;
	}else if(rx_data > SPEED_NEUTRAL){
		PORTC |= (1 << STEP1_DIR) | (1 << STEP2_DIR);							
		timer1_set_prescaler(PRESCALER_STOP);
		timer3_set_prescaler(PRESCALER_STOP);	
	}else if(rx_data > SPEED_REVERSE_1){
		PORTC |= (1 << STEP1_DIR) | (1 << STEP2_DIR);							
		*period1 = PERIOD_REVERSE_1;											
		*period3 = PERIOD_REVERSE_1;
	}else if(rx_data > SPEED_REVERSE_2){
		PORTC |= (1 << STEP1_DIR) | (1 << STEP2_DIR);							/* Change direction pin to reverse mode */
		*period1 = PERIOD_REVERSE_2;											/* Change period1 to new period that gives desired speed */
		*period3 = PERIOD_REVERSE_2;
	}else if(rx_data > SPEED_REVERSE_3){
		PORTC |= (1 << STEP1_DIR) | (1 << STEP2_DIR);							
		timer1_set_prescaler(PRESCALER_STOP);
		timer3_set_prescaler(PRESCALER_STOP);
	}
sei();
	
	
	
}