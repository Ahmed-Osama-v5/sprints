/*
 * car_sm.c
 *
 *  Created on: Dec 25, 2019
 *      Author: Ahmed
 */

#include <stdlib.h>
#include "car_sm.h"
#include "steering.h"
#include "us.h"
#include "char_lcd.h"
#include "softwareDelay.h"

#define CAR_FORWARD_80	5
#define CAR_FORWARD_30	6

static uint8 gsu8_state = CAR_STOP;

/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 80%",
 * -------------- And initiate steering and ultrasonic functions
*/
ERROR_STATUS Car_SM_Init(void)
{
	Steering_Init();
	Us_Init();
	LCD_init();
	return E_OK;
}

/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/
ERROR_STATUS Car_SM_Update(void)
{
	uint16 distance = 0;
	uint16 uSeconds = 0;
	uint8 lcdBuffer[16];

	/* Trigger pulse */
	Us_Trigger();

	/* Convert uSeconds to distance in cm */
	Us_GetDistance(&uSeconds);
	distance = (uSeconds * 64) / 58;
	sprintf(lcdBuffer, "%d CM  ", distance);
	LCD_goto_xy(0, 0);
	LCD_send_string(lcdBuffer);


	sprintf(lcdBuffer, "%d", gsu8_state);
	LCD_goto_xy(0, 1);
	LCD_send_string(lcdBuffer);

	switch(gsu8_state)
	{
	case(CAR_STOP):
		Steering_SteerCar(CAR_STOP, 50);
		break;
	case(CAR_FORWARD_80):
		Steering_SteerCar(CAR_FORWARD, 80);
		break;
	case(CAR_FORWARD_30):
		Steering_SteerCar(CAR_FORWARD, 30);
		break;
	case(CAR_BACKWARD):
		Steering_SteerCar(CAR_BACKWARD, 30);
		break;
	case(CAR_RIGHT):
		Steering_SteerCar(CAR_RIGHT, 35);
		SwDelay_ms(1500);
		break;
	default:
		break;
	}

	if(distance >= 50){
		gsu8_state = CAR_FORWARD_80;
	}
	else if((distance > 30 )){
		gsu8_state = CAR_FORWARD_30;
	}
	else if((distance == 30 )){
		gsu8_state = CAR_RIGHT;
	}
	else{
		gsu8_state = CAR_BACKWARD;
	}
	return E_OK;
}
