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
#include "interrupt.h"
#include "MotorDC.h"

extern uint16 initialValue;
extern uint16 ocr;

uint8 gu8_speed = 1;
uint16 gu16_counter = 0;

int main(){

	timer1Init(T1_NORMAL_MODE, T1_OC1_DIS, T1_PRESCALER_NO, 0, 0, 0, 0, (T1_INTERRUPT_NORMAL | T1_INTERRUPT_CMP_1A));
	timer1Start();
	sei();

	MotorDC_Init(MOT_1);
	MotorDC_Init(MOT_2);
	MotorDC_Dir(MOT_1, FORWARD);
	MotorDC_Dir(MOT_2, FORWARD);

	for(gu8_speed=1;gu8_speed<99;gu8_speed++){
		gu16_counter = 0;
		while(gu16_counter < 140){
			gu16_counter++;
			timer1SwPWM(gu8_speed, 1); // PWM @ 1 KHz with variable speed
		}
	}

	for(gu8_speed=99;gu8_speed>1;gu8_speed--){
		gu16_counter = 0;
		while(gu16_counter < 140){
			gu16_counter++;
			timer1SwPWM(gu8_speed, 1); // PWM @ 1 KHz with variable speed
		}
	}

	MotorDC_Dir(MOT_1, STOP);
	MotorDC_Dir(MOT_2, STOP);
	SwDelay_ms(1000);
	MotorDC_Dir(MOT_1, BACKWARD);
	MotorDC_Dir(MOT_2, FORWARD);

	while(gu16_counter < 500){
		gu16_counter++;
		timer1SwPWM(30, 1); // PWM @ 1 KHz with variable speed
	}

	MotorDC_Dir(MOT_1, STOP);
	MotorDC_Dir(MOT_2, STOP);
	timer1Stop();


	while(1){
		//timer1SwPWM(30, 1); // PWM @ 1 KHz with variable speed
	}
	return 0;
}


ISR(TIMER1_OVF_vect){
	gpioPinWrite(GPIOD, (BIT5 | BIT4), HIGH);
	TCNT1 = initialValue;
}

ISR(TIMER1_COMPA_vect){
	gpioPinWrite(GPIOD, (BIT5 | BIT4), LOW);
	OCR1A = ocr;
}

