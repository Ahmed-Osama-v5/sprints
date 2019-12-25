/*
 * main.c
 *
 *  Created on: Dec 22, 2019
 *      Author: Ahmed
 */

#include "interrupt.h"
#include "car_sm.h"

int main(void)
{
	Car_SM_Init();

	/* Enable global interrupts */
	sei();

	while(1)
	{
		Car_SM_Update();
	}
	return 0;
}
