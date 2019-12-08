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
#include "char_lcd.h"
#include "timers.h"


int main(){

	timer1Init(T1_NORMAL_MODE, T1_OC1_DIS, T1_PRESCALER_NO, 0, 20000, 32768, 32768, T1_POLLING);

	/* Calculating frequency */
	//uint16 f = freq * 1000;
	uint16 tcntMax = (250000 / 50);
	uint16 initialValue = 65535 - tcntMax;
	TCNT1 = initialValue;
	//TCNT1L = (uint8)initialValue;
	//TCNT1H = (uint8)(initialValue >> 8);

	/* Calculating Duty */
	OCR1A = (uint16)(tcntMax * ((float)10/100.0));
	OCR1A += initialValue;

	LCD_init();
	char lcdBuff[16];
	sprintf(lcdBuff, "OCR1A = 0x%x", OCR1A);
	LCD_goto_xy(0,0);
	LCD_send_string(lcdBuff);

	sprintf(lcdBuff, "max = %d", tcntMax);
	LCD_goto_xy(0,1);
	LCD_send_string(lcdBuff);



	while(1){

	}
	return 0;
}
