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

#define DEBUG_

#define CAR_FORWARD_80	(5)
#define CAR_FORWARD_30	(6)

#define FLAG_HIGH	(1)
#define FLAG_LOW	(0)

static uint8 gu8_state = CAR_STOP;
static uint8 gu8_RampFlag = FLAG_LOW;
static uint8 gu8_index = 0;

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
	Us_Init();
	Steering_Init();
#ifdef DEBUG_
	LCD_init();
#endif // DEBUG_
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
	uint16 u16_distance = 0;
	uint16 u16_uSeconds = 0;
	uint8 au8_lcdBuffer[16];

	/* Trigger pulse */
	Us_Trigger();

	/* Convert uSeconds to distance in cm */
	Us_GetDistance(&u16_uSeconds);
	u16_distance = (u16_uSeconds * 64) / 58;

#ifdef DEBUG_
	sprintf(au8_lcdBuffer, "%d CM  ", u16_distance);
	LCD_goto_xy(0, 0);
	LCD_send_string(au8_lcdBuffer);

	if(gu8_state == CAR_FORWARD_30)
	{
		sprintf(au8_lcdBuffer, "FORWARD_30  ");
	}
	else if(gu8_state == CAR_FORWARD_80)
	{
		sprintf(au8_lcdBuffer, "FORWARD_80  ");
	}
	else if(gu8_state == CAR_BACKWARD)
	{
		sprintf(au8_lcdBuffer, "CAR_BACKWARD");
	}
	else if(gu8_state == CAR_RIGHT)
	{
		sprintf(au8_lcdBuffer, "CAR_RIGHT   ");
	}
	else
	{

	}
	LCD_goto_xy(0, 1);
	LCD_send_string(au8_lcdBuffer);

#endif // DEBUG_

	switch(gu8_state)
	{
	case(CAR_STOP):
		gu8_RampFlag = FLAG_LOW;
		Steering_SteerCar(CAR_STOP, 50);
		SwDelay_ms(300);
		if(u16_distance > 30){
			gu8_state = CAR_FORWARD_30;
		}
		else if(u16_distance == 30){
			gu8_state = CAR_RIGHT;
		}
		else if(u16_distance < 30){
			gu8_state = CAR_BACKWARD;
		}
		else
		{
			gu8_state = CAR_STOP;
		}
		break;
	case(CAR_FORWARD_80):
		if(u16_distance >= 50){
			if(gu8_RampFlag == FLAG_LOW)
			{
				for(gu8_index=0;gu8_index<80;gu8_index++)
				{
					Steering_SteerCar(CAR_FORWARD, gu8_index);
					SwDelay_ms(10);
				}
				gu8_RampFlag = FLAG_HIGH;
			}
			else
			{
				Steering_SteerCar(CAR_FORWARD, 80);
			}
		}
		else
		{
			gu8_RampFlag = FLAG_LOW;
			gu8_state = CAR_FORWARD_30;
		}
		break;
	case(CAR_FORWARD_30):
		if(u16_distance >= 50){
			gu8_state = CAR_FORWARD_80;
		}
		else if((u16_distance < 50) && (u16_distance > 30)){
			if(gu8_RampFlag == FLAG_LOW)
			{
				for(gu8_index=0;gu8_index<40;gu8_index++)
				{
					Steering_SteerCar(CAR_FORWARD, gu8_index);
					SwDelay_ms(10);
				}
				gu8_RampFlag = FLAG_HIGH;
			}
			else
			{
				Steering_SteerCar(CAR_FORWARD, 40);
			}
		}
		else
		{
			gu8_RampFlag = FLAG_LOW;
			gu8_state = CAR_STOP;
		}
		break;
	case(CAR_BACKWARD):
		if(u16_distance < 30){
			if(gu8_RampFlag == FLAG_LOW)
			{
				for(gu8_index=0;gu8_index<32;gu8_index++)
				{
					Steering_SteerCar(CAR_BACKWARD, gu8_index);
					SwDelay_ms(10);
				}
				gu8_RampFlag = FLAG_HIGH;
			}
			else
			{
				Steering_SteerCar(CAR_BACKWARD, 32);
			}
			SwDelay_ms(2000);
			gu8_state = CAR_RIGHT;
		}
		else
		{
			gu8_RampFlag = FLAG_LOW;
			gu8_state = CAR_STOP;
		}
		break;
	case(CAR_RIGHT):
		Steering_SteerCar(CAR_STOP, gu8_index);
		SwDelay_ms(800);
		if(gu8_RampFlag == FLAG_LOW)
		{
			for(gu8_index=0;gu8_index<40;gu8_index++)
			{
				Steering_SteerCar(CAR_RIGHT, gu8_index);
				SwDelay_ms(10);
			}
			gu8_RampFlag = FLAG_HIGH;
		}
		else
		{
			Steering_SteerCar(CAR_RIGHT, 40);
		}
		SwDelay_ms(2000);
		gu8_RampFlag = FLAG_LOW;
		gu8_state = CAR_STOP;
		break;
	default:
		break;
	}
	return E_OK;
}
