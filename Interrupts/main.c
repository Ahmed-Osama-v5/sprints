/*
 * main.c
 *
 *  Created on: Dec 14, 2019
 *      Author: Ahmed Osama
 */
#include "registers.h"
#include "gpio.h"
#include "timers.h"
#include "interrupt.h"

extern uint16 initialValue;
extern uint16 ocr;

int main(void){

	gpioPinDirection(GPIOD, BIT5, OUTPUT);

	timer1Init(T1_NORMAL_MODE, T1_OC1_DIS, T1_PRESCALER_NO, 0, 0, 0, 0, (T1_INTERRUPT_NORMAL | T1_INTERRUPT_CMP_1A));
	timer1Start();
	sei();

	while(1){
		timer1SwPWM(60, 5);
	}
	return 0;
}

ISR(TIMER1_OVF_vect){
	gpioPinWrite(GPIOD, BIT5, HIGH);
	TCNT1 = initialValue;
}

ISR(TIMER1_COMPA_vect){
	gpioPinWrite(GPIOD, BIT5, LOW);
	OCR1A = ocr;
}
