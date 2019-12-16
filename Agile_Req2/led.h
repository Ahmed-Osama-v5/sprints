/*
 * led.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef LED_H_
#define LED_H_

#include "gpio.h"
#include "std_types.h"
#include "ledConfig.h"

typedef enum En_LedNumber_t{
	LED_0,
	LED_1,
	LED_2,
	LED_3
}En_LedNumber_t;

/**
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Init(En_LedNumber_t led_id);
/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be on
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_On(En_LedNumber_t led_id);
/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be off
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Off(En_LedNumber_t led_id);
/**
 * Description: Toggle the LED_x state (where x 0, 1, 2, 3)
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Toggle(En_LedNumber_t led_id);



#endif /* LED_H_ */
