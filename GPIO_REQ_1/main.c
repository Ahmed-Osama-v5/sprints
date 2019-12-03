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

int main(){

	Led_Init(LED_0);

	while(1){
		Led_Toggle(LED_0);
		SwDelay_ms(1000);
	}
	return 0;
}
