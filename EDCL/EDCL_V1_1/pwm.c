/*
 * pwm.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

/*************************************************
*Title  : Test PWM Library.
*Author : Eng/Ahmed Osama.
*Date   : 15 Jun 2015.
*Contact: engahmed2015@gmail.com.
**************************************************/

#include <avr/io.h>
#include "pwm.h"

void PWM0_init()
{
    TCCR0 |= (1 << WGM00) | (2 << COM00);
    TCNT0 = 0;
    DDRB |= (1 << PINB3);
}

void PWM0_Stop()
{
    TCCR0 &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
    TCCR0 &= ~((1 << COM00) | (1 << COM01));
}

void PWM0_Start()
{
    TCCR0 |= (2 << COM00);
    TCCR0 |= (1 << CS01);
}

void PWM0_Set_Duty(unsigned char Duty)
{
    OCR0 = Duty;
}

void PWM2_init()
{
    TCCR2 |= (1 << WGM20) | (2 << COM20);
    TCNT2 = 0;
    DDRD |= (1 << PIND7);
}

void PWM2_Stop()
{
    TCCR2 &= ~((1 << CS20) | (1 << CS21) | (1 << CS22));
    TCCR2 &= ~((1 << COM20) | (1 << COM21));
}

void PWM2_Start()
{
    TCCR2 |= (2 << COM20);
    TCCR2 |= (1 << CS21);
}

void PWM2_Set_Duty(unsigned char Duty)
{
    OCR2 = Duty;
}

