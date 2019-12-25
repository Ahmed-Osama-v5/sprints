/*
 * motor.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Ahmed
 */

#include "motor.h"
#include "dio.h"
#include "pwm.h"

#define INITIALIZED			1
#define NOT_INITIALIZED		0

#define MAX_MOTOR_NUMBER	2

#define MOTOR_FREQUENCY		1000

static uint8 gsu8_initState[MAX_MOTOR_NUMBER] = {NOT_INITIALIZED};

/**
 * Func			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
 ERROR_STATUS Motor_Init(uint8 Motor_Number)
 {
		 DIO_Cfg_s ST_dio1 = {0};
		 DIO_Cfg_s ST_dio2 = {0};
		 Pwm_Cfg_s_t ST_Pwm = {0};
		 switch (Motor_Number)
		 {
		 case (MOTOR_1):
		 	/* set IN1 as digital output */
			ST_dio1.GPIO = GPIOD;
		 	ST_dio1.dir = OUTPUT;
		 	ST_dio1.pins = PIN2;
		 	if(DIO_init(&ST_dio1) == E_OK)
		 	{

		 	}
		 	else
		 	{
		 	 return E_NOK;
		 	}
		 	/* set IN2 as digital output */
		 	ST_dio1.GPIO = GPIOD;
		 	ST_dio1.pins = PIN3;
		 	if(DIO_init(&ST_dio1) == E_OK)
		 	{

		 	}
		 	else
		 	{
		 	 return E_NOK;
		 	}
		 	/* Init PWM CH1A */
		 	ST_Pwm.channel = PWM_CH1A;
		 	ST_Pwm.prescaler = PWM_PRESCALER_NO;
		 	Pwm_Init(&ST_Pwm);
			gsu8_initState[0] = INITIALIZED;
		 	break;
		 case (MOTOR_2):
			/* set IN3 as digital output */
			ST_dio2.GPIO = GPIOD;
		 	ST_dio2.dir = OUTPUT;
		 	ST_dio2.pins = PIN6;
			if(DIO_init(&ST_dio2) == E_OK)
			{

			}
			else
			{
			 return E_NOK;
			}
			/* set IN4 as digital output */
			ST_dio2.GPIO = GPIOD;
			ST_dio2.pins = PIN7;
			if(DIO_init(&ST_dio2) == E_OK)
			{

			}
			else
			{
			 return E_NOK;
			}
			/* Init PWM CH1B */
			ST_Pwm.channel = PWM_CH1B;
			ST_Pwm.prescaler = PWM_PRESCALER_NO;
			Pwm_Init(&ST_Pwm);
			gsu8_initState[1] = INITIALIZED;
			break;
		 default:
			return E_NOK;
			break;
		}
	 return E_OK;
 }

/**
 * Fun		 : Motor_Direction
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2

			   @param Motor_Direction
			   #define
			   Stop, Forward, Backword
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor direction from getting the motor number and the direction.
*/
ERROR_STATUS Motor_Direction(uint8 Motor_Number, uint8 Motor_Direction)
{
	if(gsu8_initState[Motor_Number] == INITIALIZED)
	{
		switch(Motor_Number)
		{
		case (MOTOR_1):
			if(Motor_Direction == MOTOR_FORWARD)
			{
				DIO_Write(GPIOD, PIN2, HIGH);
				DIO_Write(GPIOD, PIN3, LOW);
			}
			else if(Motor_Direction == MOTOR_BACKWORD)
			{
				DIO_Write(GPIOD, PIN2, LOW);
				DIO_Write(GPIOD, PIN3, HIGH);
			}
			else
			{
				return E_NOK;
			}
			break;
		case (MOTOR_2):
			if(Motor_Direction == MOTOR_FORWARD)
			{
				DIO_Write(GPIOD, PIN6, HIGH);
				DIO_Write(GPIOD, PIN7, LOW);
			}
			else if(Motor_Direction == MOTOR_BACKWORD)
			{
				DIO_Write(GPIOD, PIN6, LOW);
				DIO_Write(GPIOD, PIN7, HIGH);
			}
			else
			{
				return E_NOK;
			}
			break;
		default:
			return E_NOK;
			break;
		}
	}
	else
	{
		return E_NOK;
	}

	 return E_OK;
}

/**
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Start the motor.
*/
ERROR_STATUS Motor_Start(uint8 Motor_Number, uint8 Mot_Speed)
{
	if(gsu8_initState[Motor_Number] == INITIALIZED)
	{
		switch(Motor_Number)
		{
		case (MOTOR_1):
			Pwm_Start(PWM_CH1A, Mot_Speed, MOTOR_FREQUENCY);
			break;
		case (MOTOR_2):
			Pwm_Start(PWM_CH1B, Mot_Speed, MOTOR_FREQUENCY);
			break;
		default:
			return E_NOK;
			break;
		}
	}
	else
	{
		return E_NOK;
	}
	 return E_OK;
}

/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Descriptio: Controls the motor speed from getting the motor number and the speed.
*/
ERROR_STATUS Motor_SpeedUpdate(uint8 Motor_Number, uint8 Speed)
{
	if(gsu8_initState[Motor_Number] == INITIALIZED)
	{
		switch(Motor_Number)
		{
		case (MOTOR_1):
			Pwm_Update(PWM_CH1A, Speed, MOTOR_FREQUENCY);
			break;
		case (MOTOR_2):
			Pwm_Update(PWM_CH1B, Speed, MOTOR_FREQUENCY);
			break;
		default:
			return E_NOK;
			break;
		}
	}
	else
	{
		return E_NOK;
	}
	 return E_OK;
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: stop the motor.
*/
ERROR_STATUS Motor_Stop(uint8 Motor_Number)
{
	if(gsu8_initState[Motor_Number] == INITIALIZED)
	{
		switch(Motor_Number)
		{
		case (MOTOR_1):
			Pwm_Stop(PWM_CH1A);
			DIO_Write(GPIOD, PIN2, LOW);
			DIO_Write(GPIOD, PIN3, LOW);
			break;
		case (MOTOR_2):
			Pwm_Stop(PWM_CH1B);
			DIO_Write(GPIOD, PIN6, LOW);
			DIO_Write(GPIOD, PIN7, LOW);
			break;
		default:
			return E_NOK;
			break;
		}
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

 /**
 * Func			: Motor_GetStatus
 * Input		: Motor_Number
 *	  	  		 #def
 *	  	  		 number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: Initialization_STATUS
 * Description	: Returns status of the motor whether intialized or not
 */
 uint8 Motor_GetStatus(uint8 Motor_Number)
 {
	 if(gsu8_initState[Motor_Number] == INITIALIZED)
	 {
		 return 1;
	 }
	 else
	 {
		 return 0;
	 }
 }
