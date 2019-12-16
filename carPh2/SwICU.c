/*
 * SwICU.c
 *
 *  Created on: Dec 15, 2019
 *      Author: Ahmed
 */

#include "SwICU.h"
#include "timers.h"
#include "gpio.h"
#include "softwareDelay.h"

volatile uint8 gvu8_OVFs = 0;
volatile uint8 gvu8_uSeconds = 0;

void SwICU_Init(SwICU_Edge_TypeDef inputCaptureEdge){
	timer0Init(T0_NORMAL_MODE, T0_OC0_DIS, T0_PRESCALER_1024, 0, 0, T0_INTERRUPT_NORMAL);
	gpioPinDirection(GPIOB, BIT3, OUTPUT);
	switch (inputCaptureEdge) {
		case (SwICU_EdgeFalling):
			MCUCSR &= ~(1 << 6);
			break;
		case (SwICU_EdgeRisiging):
			MCUCSR |= (1 << 6);
			break;
		default:
			MCUCSR |= (1 << 6);
			break;
	}
	SwICU_Enable();
}

SwICU_Edge_TypeDef SwICU_GetCfgEdge(void){
	if(MCUCSR & (1 << 6))
		return SwICU_EdgeRisiging;
	else
		return SwICU_EdgeFalling;
}

void SwICU_SetCfgEdge(SwICU_Edge_TypeDef edge){
	switch (edge) {
		case (SwICU_EdgeFalling):
			MCUCSR &= ~(1 << 6);
			break;
		case (SwICU_EdgeRisiging):
			MCUCSR |= (1 << 6);
			break;
		default:
			MCUCSR |= (1 << 6);
			break;
	}
}

void SwICU_Read(volatile uint8 * capt){
	PORTB_DATA |= (1 << 3); // trigger pin high
	SwDelay_us(10);
	PORTB_DATA &= ~(1 << 3); // trigger pin low
	SwDelay_us(500);
	*capt = gvu8_uSeconds;
}

void SwICU_Stop(void){
	TCCR0 = T0_NO_CLOCK; // stop timer0
}

void SwICU_Start(void){
	TCCR0 |= T0_PRESCALER_1024; // start timer0
}

void SwICU_Enable(void){
	GICR |= (1 << 5); // enable INT2
}

void SwICU_Disable(void){
	GICR &= ~(1 << 5); // disable INT2
}

ISR(INT2_vect){
	if(SwICU_GetCfgEdge() == SwICU_EdgeRisiging){
		SwICU_Start();
		SwICU_SetCfgEdge(SwICU_EdgeFalling);
	}
	else{
		SwICU_Stop();
		gvu8_uSeconds = TCNT0;
		TCNT0 = 0;
		//gvu8_OVFs = 0;
		SwICU_SetCfgEdge(SwICU_EdgeRisiging);
	}
	//MCUCSR ^= (1 << 6);
}

ISR(TIMER0_OVF_vect){
	gvu8_OVFs++;
}
