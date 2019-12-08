/*
 * main.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Ahmed Osama
 */

#include <stdio.h>
#include "registers.h"
#include "gpio.h"
#include "softwareDelay.h"
#include "led.h"
#include "pushButton.h"
#include "timers.h"
#include "char_lcd.h"

#define PWM
//#define REQ8_6
//#define REQ8_7

#ifdef PWM


int main(){

	LCD_init();
	LCD_send_string("Test");

	gpioPinDirection(GPIOB, BIT4, OUTPUT);
	timer1Init(T1_NORMAL_MODE, T1_OC1_DIS, T1_PRESCALER_64, 60000, 60000, 60000, 60000, T1_POLLING);


	while(1){
		timer1SwPWM(50, 250);
	}
	return 0;
}

#endif // PWM

#ifdef REQ8_6

uint8 gu8_counter = 0;
uint8 gu8_onFlag = 0;
uint8 gu8_value = 5;


int main(){

	Led_Init(LED_1);
	pushButton_Init(BTN_1);

	while(1){
		pushButton_Update();
		if(pushButton_GetStatus(BTN_1) == Pressed){
			Led_On(LED_1);
			if(gu8_onFlag == 1){
				gu8_counter = 0;
				gu8_value = 10;
			}
			else
				gu8_onFlag = 1;
		}
		else{
			if(!gu8_onFlag){
				Led_Off(LED_1);
				gu8_onFlag = 0;
				gu8_value = 5;
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

#endif // REQ8_6

#ifdef REQ8_7

typedef enum{
	GO,
	STOP,
	GET_READY
}En_runState_t;

int main(){

	En_runState_t mode = GO;
	timer1Init(T1_COMP_MODE_ICR1_TOP, T1_OC1_DIS, T1_PRESCALER_64, 6, 249, 249, 249, T1_POLLING);

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
		timer1Delay_ms(1000);
	}
	return 0;
}

#endif // REQ8_7
