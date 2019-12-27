/*
 * main.c
 *
 *  Created on: Dec 22, 2019
 *      Author: Ahmed
 */

#include "interrupt.h"
#include "car_sm.h"

#define DEBUG_LED

#ifdef DEBUG_LED

#include "timer.h"
#include "dio.h"

DIO_Cfg_s str_Dio_cfg = {0};
Timer_cfg_s str_Timer_cfg = {0};


#endif // DEBUG_LED

void Timer2_CBK_Func(void);

int main(void)
{
#ifdef DEBUG_LED
	/* Initialize a heart beat Led */
	str_Dio_cfg.GPIO = GPIOB;
	str_Dio_cfg.dir = OUTPUT;
	str_Dio_cfg.pins = PIN6;
	DIO_init(&str_Dio_cfg);

	/* Initialize a heart beat Timer */
	str_Timer_cfg.Timer_CH_NO = TIMER_CH2;
	str_Timer_cfg.Timer_Mode = TIMER_MODE;
	str_Timer_cfg.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
	str_Timer_cfg.Timer_Prescaler = TIMER_PRESCALER_1024;
	str_Timer_cfg.CBK_Ptr = Timer2_CBK_Func;
	Timer_Init(&str_Timer_cfg);
	Timer_Start(TIMER_CH2, 255);
#endif // DEBUG_LED

	Car_SM_Init();

	/* Enable global interrupts */
	sei();

	while(1)
	{
		Car_SM_Update();
	}
	return 0;
}

void Timer2_CBK_Func(void)
{
	DIO_Toggle(GPIOB, PIN6);
}
