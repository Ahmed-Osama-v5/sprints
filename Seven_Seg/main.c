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
#include "interrupt.h"
#include "sevenSeg_BCD.h"

int main(){

	sevenSeg_Init();
	//sevenSeg_Write(SEG_0, 3);

	// 0
	gpioPinWrite(SEG_BCD_GPIO, BIT0, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, LOW);
	SwDelay_ms(1000);

	// 1
	gpioPinWrite(SEG_BCD_GPIO, BIT0, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, LOW);
	SwDelay_ms(1000);

	// 2
	gpioPinWrite(SEG_BCD_GPIO, BIT0, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, LOW);
	SwDelay_ms(1000);

	// 3
	gpioPinWrite(SEG_BCD_GPIO, BIT0, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, LOW);
	SwDelay_ms(1000);

	// 4
	gpioPinWrite(SEG_BCD_GPIO, BIT0, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, LOW);
	SwDelay_ms(1000);

	// 5
	gpioPinWrite(SEG_BCD_GPIO, BIT0, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, LOW);
	SwDelay_ms(1000);

	// 6
	gpioPinWrite(SEG_BCD_GPIO, BIT0, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, LOW);
	SwDelay_ms(1000);

	// 7
	gpioPinWrite(SEG_BCD_GPIO, BIT0, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, LOW);
	SwDelay_ms(1000);

	// 8
	gpioPinWrite(SEG_BCD_GPIO, BIT0, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, HIGH);
	SwDelay_ms(1000);

	// 9
	gpioPinWrite(SEG_BCD_GPIO, BIT0, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, HIGH);
	SwDelay_ms(1000);

	// 10
	gpioPinWrite(SEG_BCD_GPIO, BIT0, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, HIGH);
	SwDelay_ms(1000);

	// 11
	gpioPinWrite(SEG_BCD_GPIO, BIT0, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, HIGH);
	SwDelay_ms(1000);

	// 12
	gpioPinWrite(SEG_BCD_GPIO, BIT0, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, HIGH);
	SwDelay_ms(1000);

	// 13
	gpioPinWrite(SEG_BCD_GPIO, BIT0, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, HIGH);
	SwDelay_ms(1000);

	// 14
	gpioPinWrite(SEG_BCD_GPIO, BIT0, LOW);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, HIGH);
	SwDelay_ms(1000);

	// 15
	gpioPinWrite(SEG_BCD_GPIO, BIT0, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT1, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT2, HIGH);
	gpioPinWrite(SEG_BCD_GPIO, BIT3, HIGH);
	SwDelay_ms(1000);

	while(1){
	}
	return 0;
}
