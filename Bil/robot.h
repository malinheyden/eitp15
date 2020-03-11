/*
 * robot.h
 *
 * Created: 2020-02-25 17:50:22
 *  Author: elt14iob
 */ 


#ifndef ROBOT_H_
#define ROBOT_H_
#include <avr/io.h>
#include <avr/interrupt.h>



/** <define STEP1*/
/** < Define pins for Driver_1 STEP signal in PD5*/
#define STEP1_STEP			(0x05)

/** < Define pins for Driver_1 MODE signals in PA0 | PA1 | PA2 */
#define STEP1_MODE0			(0x00)
#define STEP1_MODE1			(0x01)
#define STEP1_MODE2			(0x02)

/** < Define bits for Driver_1 MODE state, for bottom 3 LSB in PA*/
#define MICRO_STEP1_1		(0x00)
#define MICRO_STEP1_2		(0x01)
#define MICRO_STEP1_4		(0x02)
#define MICRO_STEP1_8		(0x03)
#define MICRO_STEP1_16		(0x04)
#define MICRO_STEP1_32		(0x05)

/** < Define pin for Driver_1 DIR signal in PC0*/
#define STEP1_DIR			(0x00)


/** <define STEP2*/
/** < Define pins for Driver_2 STEP signal in PB6*/
#define STEP2_STEP			(0x06)

/** < Define pins for Driver_2 MODE signals in PA5 | PA6 | PA7 */
#define STEP2_MODE0			(0x05)
#define STEP2_MODE1			(0x06)
#define STEP2_MODE2			(0x07)
	
/** < Define bits for Driver_2 MODE state, shift 5 steps for top 3 MSB in PA*/
#define MICRO_STEP2_1		(MICRO_STEP1_1 << 5)
#define MICRO_STEP2_2		(MICRO_STEP1_2 << 5)
#define MICRO_STEP2_4		(MICRO_STEP1_4 << 5)
#define MICRO_STEP2_8		(MICRO_STEP1_8 << 5)
#define MICRO_STEP2_16		(MICRO_STEP1_16 << 5)
#define MICRO_STEP2_32		(MICRO_STEP1_32 << 5)

/** < Define pin for Driver_2 DIR signal in PC1*/	
#define STEP2_DIR			(0x01)

/** < Define speed stages of input data range */
#define SPEED_REVERSE_3		102
#define SPEED_REVERSE_2		109
#define SPEED_REVERSE_1		116
#define SPEED_NEUTRAL		124
#define SPEED_1				131
#define SPEED_2				138
#define SPEED_3				144

/** <Define period time for set stepper motor speed*/
#define PERIOD_REVERSE_1	(PERIOD_1 + 10)
#define PERIOD_REVERSE_2	(PERIOD_2 + 10)
#define PERIOD_REVERSE_3	(PERIOD_3 + 10)
#define PERIOD_1			35
#define PERIOD_2			30
#define PERIOD_3			25
#define PERIOD_TOP			13

#define DRIVER_INT			40

/** < Define speed stages of input data range */
#define DIRECTION_LEFT_3	SPEED_REVERSE_3
#define DIRECTION_LEFT_2	SPEED_REVERSE_2
#define DIRECTION_LEFT_1	SPEED_REVERSE_1
#define DIRECTION_NEUTRAL	SPEED_NEUTRAL
#define DIRECTION_RIGHT_1	SPEED_1	
#define DIRECTION_RIGHT_2	SPEED_2				
#define DIRECTION_RIGHT_3	SPEED_3				



/**
*	Determines the direction of the stepper motor.
*	@param rx_data is one of the input data bytes from controller unit
*	@return	the direction of the stepper motor, either 1 or 0
*/
void driver_speed(uint8_t rx_data, uint8_t *period, uint8_t *period3);


/**
*	Determines the speed of the stepper motor.
*	@param rx_data is one of the input data bytes from controller unit
*	@return	the speed of the stepper motor, not lower then (0x0C)
*/
void driver_direction(uint8_t rx_data, uint8_t *direction1, uint8_t *direction3);


#endif /* ROBOT_H_ */