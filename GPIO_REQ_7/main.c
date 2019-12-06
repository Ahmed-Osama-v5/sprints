/*
 * main.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Ahmed Osama
 */

#include "registers.h"
#include "gpio.h"
#include "softwareDelay.h"
#include "led.h"
#include "pushButton.h"

typedef enum{
	GO,
	STOP,
	GET_READY
}En_runState_t;

int main(){

	En_runState_t mode = GO;

	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);

	while(1){

		switch (mode) {
			case (GO):
				Led_Off(LED_2);
				Led_Off(LED_3);
				Led_On(LED_1);
				mode = STOP;
				break;
			case (STOP):
				Led_Off(LED_1);
				Led_Off(LED_3);
				Led_On(LED_2);
				mode = GET_READY;
				break;
			case (GET_READY):
				Led_Off(LED_1);
				Led_Off(LED_2);
				Led_On(LED_3);
				mode = GO;
				break;
			default:
				break;
		}
		SwDelay_ms(1000);
	}
	return 0;
}
