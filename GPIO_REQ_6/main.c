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

uint8 counter = 0;

int main(){

	Led_Init(LED_1);
	pushButton_Init(BTN_1);

	while(1){
		pushButton_Update();
		switch(g_pb_1_State){
		case(Pressed):
			counter++;
			Led_On(LED_1);
			break;
		case(Released):
			Led_Off(LED_1);
			break;
		default:
			Led_Off(LED_1);
			break;
		}
		SwDelay_ms(1000);
	}
	return 0;
}
