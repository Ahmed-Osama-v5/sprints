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
#include "timers.h"
#include "interrupt.h"
#include "SwICU.h"
#include "led.h"

//#define DEBUG_

#define AGILE_REQ_2

uint8 dist;
uint16 measure;
//char lcdBuffer[16];

int main(){

#ifdef AGILE_REQ_2
	Led_Init(LED_0);
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
#endif

	SwICU_Init(SwICU_EdgeRisiging);
	sei();
#ifdef DEBUG_
	LCD_init();
	LCD_send_string("Dist = ");
#endif // DEBUG_


	while(1){
		SwICU_Read(&dist);
		measure = (dist * 64);
		measure /= 58;
#ifdef DEBUG_
		//SwDelay_ms(300);
		sprintf(lcdBuffer, "%d CM  ", measure);
		LCD_goto_xy(7, 0);
		LCD_send_string(lcdBuffer);
		//SwDelay_ms(300);
#endif // DEBUG_

#ifdef AGILE_REQ_2
		if(measure <= 240){
			measure /= 16;
			if(measure < 16)
				measure |= (1 << 0);
			if(measure & (1 << 0))
				Led_On(LED_0);
			else
				Led_Off(LED_0);
			if(measure & (1 << 1))
				Led_On(LED_1);
			else
				Led_Off(LED_1);
			if(measure & (1 << 2))
				Led_On(LED_2);
			else
				Led_Off(LED_2);
			if(measure & (1 << 3))
				Led_On(LED_3);
			else
				Led_Off(LED_3);
		}
		else{
			Led_On(LED_0);
			Led_On(LED_1);
			Led_On(LED_2);
			Led_On(LED_3);
		}
#endif
#ifdef DEBUG_
		//SwDelay_ms(300);
		sprintf(lcdBuffer, "%d ", measure);
		LCD_goto_xy(0, 1);
		LCD_send_string(lcdBuffer);
		SwDelay_ms(300);
#endif // DEBUG_
	}
	return 0;
}
