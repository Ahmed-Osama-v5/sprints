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

int main(){

	Led_Init(LED_0);
	Led_Init(LED_1);
	pushButton_Init(BTN_0);
	pushButton_Init(BTN_1);

	while(1){
		pushButton_Update();
		if(pushButton_GetStatus(BTN_0) == Pressed){
			Led_Toggle(LED_0);
		}
		if(pushButton_GetStatus(BTN_1) == Pressed){
			Led_Toggle(LED_1);
		}
	}
	return 0;
}
