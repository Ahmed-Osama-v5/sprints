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

uint8 gu8_counter = 0;
uint8 gu8_onFlag = 0;
uint8 gu8_value = 10;

int main(){

	Led_Init(LED_1);
	pushButton_Init(BTN_1);

	while(1){
		if(pushButton_GetStatus(BTN_1) == Pressed){
			Led_On(LED_1);
			if(gu8_onFlag == 1){
				gu8_counter = 0;
				gu8_value = 20;
			}
			else
				gu8_onFlag = 1;
		}
		else{
			if(!gu8_onFlag){
				Led_Off(LED_1);
				gu8_onFlag = 0;
				gu8_value = 10;
			}
		}
		if(gu8_onFlag){
			if(gu8_counter < gu8_value)
				gu8_counter++;
			else{
				gu8_onFlag = 0;
				gu8_counter = 0;
			}
		}
	}
	return 0;
}
