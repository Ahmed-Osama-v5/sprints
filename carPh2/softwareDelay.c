/*
 * softwareDelay.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Ahmed Osama
 */

#include "std_types.h"
#include "softwareDelay.h"

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the milli-seconds
 */
void SwDelay_ms(uint32 n){
	n *= 735;
	while(n--){
		asm("nop");
	}
}

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the micro-seconds
 */
void SwDelay_us(uint32 n){
	uint32 i;
	for(i=0;i<n;i++){
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}
}
