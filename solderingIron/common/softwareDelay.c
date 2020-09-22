/*
 * softwareDelay.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Ahmed Osama
 */

//#include "std_types.h"
#include "softwareDelay.h"
static void delay_loop_2(volatile uint16 counter)
{
	while(counter--)
	{
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
	}
}

static void delay_loop_1(volatile uint8 counter)
{
	while(counter--)
	{
		asm("NOP");
		asm("NOP");
		asm("NOP");
	}
}

/**
 * @brief this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param __ms: the milli-seconds
 */
void SwDelay_ms(double __ms){
	__ms /= 10;
	uint32 __tmp;
	uint16 __ticks;
	       __tmp = ((F_CPU) / 4e3) * __ms;
	       if (__tmp < 1.0)
	           __ticks = 1;
	       else if (__tmp > 65535)
	       {
	           //  __ticks = requested delay in 1/10 ms
	           __ticks = (uint16) (__ms * 10.0);
	           while(__ticks)
	           {
	               // wait 1/10 ms
	        	   delay_loop_2(((F_CPU) / 4e3) / 10);
	               __ticks --;
	           }
	           return;
	       }
	       else
	           __ticks = (uint16)__tmp;
	       delay_loop_2(__ticks);
}

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the micro-seconds
 */
void SwDelay_us(double __us){
	double __tmp ;
	uint8 __ticks = 0;
	double __tmp2 ;
	__tmp = ((F_CPU) / 3e6) * __us;
	__tmp2 = ((F_CPU) / 4e6) * __us;
	if (__tmp < 1.0)
	   __ticks = 1;
	else if (__tmp2 > 65535)
	{
		SwDelay_ms(__us / 1000.0);
	}
	else if (__tmp > 255)
	{
	   uint16 __ticks=(uint16)__tmp2;
	   delay_loop_2(__ticks);
	   return;
	}
	else
	   __ticks = (uint8)__tmp;
	delay_loop_1(__ticks);
}
