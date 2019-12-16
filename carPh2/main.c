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
#include "char_lcd.h"
#include "timers.h"
#include "interrupt.h"
#include "SwICU.h"
#include "HwPWM.h"
#include "MotorDC.h"
#include "led.h"

//#define DEBUG_

uint8 dist;
uint16 measure;
extern volatile uint8 gvu8_OVFs;
uint16 gu16_counter = 0;

int main(){
	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1, FORWARD);
	MotorDC_Dir(MOT_2, FORWARD);

	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);

	HwPWM_Init();

	SwICU_Init(SwICU_EdgeRisiging);

	sei();
#ifdef DEBUG_
	char lcdBuffer[16];
	LCD_init();
	LCD_send_string("Dist = ");
#endif // DEBUG_

	while(1){
		SwICU_Read(&dist);
		measure = ((dist + (gvu8_OVFs * 256)) * 64);
		gvu8_OVFs = 0;
		measure /= 58;
		MotorDC_Dir(MOT_1, FORWARD);
		MotorDC_Dir(MOT_2, FORWARD);

		if(measure >= 50){
			MotorDC_Speed_HwPWM(80);
			Led_Off(LED_1);
			Led_Off(LED_2);
			Led_Off(LED_3);
			Led_On(LED_0);
		}
		else if((measure > 30 )){
			MotorDC_Speed_HwPWM(30);
			Led_Off(LED_0);
			Led_Off(LED_2);
			Led_Off(LED_3);
			Led_On(LED_1);
		}
		else if((measure == 30 )){
			Led_Off(LED_0);
			Led_Off(LED_1);
			Led_Off(LED_3);
			Led_On(LED_2);
			MotorDC_Dir(MOT_1, STOP);
			MotorDC_Dir(MOT_2, STOP);
			SwDelay_ms(100);
			MotorDC_Dir(MOT_1, BACKWARD);
			MotorDC_Dir(MOT_2, FORWARD);
			SwDelay_ms(100);

			while(gu16_counter < 500){
				gu16_counter++;
				MotorDC_Speed_HwPWM(50); // turn right
			}
			gu16_counter = 0;
		}
		else{
			Led_Off(LED_0);
			Led_Off(LED_1);
			Led_Off(LED_2);
			Led_On(LED_3);
			MotorDC_Dir(MOT_1, STOP);
			MotorDC_Dir(MOT_2, STOP);
			SwDelay_ms(200);
			MotorDC_Dir(MOT_1, BACKWARD);
			MotorDC_Dir(MOT_2, BACKWARD);
			SwDelay_ms(100);
		}


#ifdef DEBUG_
		//SwDelay_ms(300);
		sprintf(lcdBuffer, "%d CM  ", measure);
		LCD_goto_xy(7, 0);
		LCD_send_string(lcdBuffer);
		//SwDelay_ms(300);
#endif // DEBUG_

	}
	return 0;
}
