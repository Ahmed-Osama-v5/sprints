/*
 * keypad.h
 *
 *  Created on: Mar 7, 2019
 *      Author: Ahmed
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdint.h>
#include <stdio.h>

//KEYPAD IS ATTACHED ON PORTA

//Don't Touch the lines below
//*******************************
#define KEYPAD_PORT  	PORTC
#define KEYPAD_DDR   	DDRC
#define KEYPAD_PIN   	PINC
//*******************************
#define UP           	6
#define DOWN         	4
#define RIGHT        	3
#define LEFT		 	7
#define OK  			5

#define UP_KEY          0xB8
#define DOWN_KEY        0xE8
#define RIGHT_KEY       0xF0
#define LEFT_KEY		0x78
#define OK_KEY			0xD8

#define NO_KEY_PRESSED	0xFF

 uint8_t GetKeyPressed();


#endif /* KEYPAD_H_ */
