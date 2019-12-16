/*
 * gpio.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Ahmed Osama
 */


#include "std_types.h"
#include "registers.h"
#include "gpio.h"

/*===========================PORT Control===============================*/
/**
 * Description: set port direction (which is DDR register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction: set the port direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
void gpioPortDirection(uint8 port, uint8 direction){
	switch(port){
	case (GPIOA):
		PORTA_DIR = direction;
		break;
	case (GPIOB):
		PORTB_DIR = direction;
		break;
	case (GPIOC):
		PORTC_DIR = direction;
		break;
	case (GPIOD):
		PORTD_DIR = direction;
		break;
	default: // PORTA
		PORTA_DIR = direction;
		break;
	}
}

/**
 * Description: set the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value: set the port value and takes the following values
 * 				- 0x00 -> Low
 * 				- 0xff -> High
 */
void gpioPortWrite(uint8 port, uint8 value){
	switch(port){
	case (GPIOA):
		PORTA_DATA = value;
		break;
	case (GPIOB):
		PORTB_DATA = value;
		break;
	case (GPIOC):
		PORTC_DATA = value;
		break;
	case (GPIOD):
		PORTD_DATA = value;
		break;
	default: // PORTA
		PORTA_DATA = value;
		break;
	}
}

/**
 * Description: toggle the port value (which is PORT register)
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */
void gpioPortToggle(uint8 port){
	switch(port){
	case (GPIOA):
		PORTA_DATA = PORTA_DATA ^ 0xFF;
		break;
	case (GPIOB):
		PORTB_DATA = PORTB_DATA ^ 0xFF;
		break;
	case (GPIOC):
		PORTC_DATA = PORTC_DATA ^ 0xFF;
		break;
	case (GPIOD):
		PORTD_DATA = PORTD_DATA ^ 0xFF;
		break;
	default: // PORTA
		PORTA_DATA = PORTA_DATA ^ 0xFF;
		break;
	}
}

/**
 * Description: read the current port value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioPortRead(uint8 port){
	switch(port){
	case (GPIOA):
		return PORTA_PIN;
		break;
	case (GPIOB):
		return PORTB_PIN;
		break;
	case (GPIOC):
		return PORTC_PIN;
		break;
	case (GPIOD):
		return PORTD_PIN;
		break;
	default: // PORTA
		return PORTA_PIN;
		break;
	}
}

/*===========================PIN Control===============================*/
/**
 * Description: set selected pins (more than one pin [ORed]) direction
 *
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to set its direction and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 *
 * @param direction: set the pins direction and takes the following values
 * 				- 0x00 -> Input
 * 				- 0xff -> Output
 */
void gpioPinDirection(uint8 port, uint8 pins, uint8 direction){
	switch(port){
	case (GPIOA):
		if(direction == OUTPUT)
			PORTA_DIR |= pins;
		else
			PORTA_DIR &= ~pins;
		break;
	case (GPIOB):
		if(direction == OUTPUT)
			PORTB_DIR |= pins;
		else
			PORTB_DIR &= ~pins;
		break;
	case (GPIOC):
		if(direction == OUTPUT)
			PORTC_DIR |= pins;
		else
			PORTC_DIR &= ~pins;
		break;
	case (GPIOD):
		if(direction == OUTPUT)
			PORTD_DIR |= pins;
		else
			PORTD_DIR &= ~pins;
		break;
	default: // PORTA
		if(direction == OUTPUT)
			PORTA_DIR |= pins;
		else
			PORTA_DIR &= ~pins;
		break;
	}
}

/**
 * Description: set selected pins (more than one pin [ORed]) values
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pins the user need to write its values and takes
 * 				any member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @param value
 */
void gpioPinWrite(uint8 port, uint8 pins, uint8 value){
	switch(port){
	case (GPIOA):
		if(value == HIGH)
			PORTA_DATA |= pins;
		else
			PORTA_DATA &= ~pins;
		break;
	case (GPIOB):
		if(value == HIGH)
			PORTB_DATA |= pins;
		else
			PORTB_DATA &= ~pins;
		break;
	case (GPIOC):
		if(value == HIGH)
			PORTC_DATA |= pins;
		else
			PORTC_DATA &= ~pins;
		break;
	case (GPIOD):
		if(value == HIGH)
			PORTD_DATA |= pins;
		else
			PORTD_DATA &= ~pins;
		break;
	default: // PORTA
		if(value == HIGH)
			PORTA_DATA |= pins;
		else
			PORTA_DATA &= ~pins;
		break;
	}
}

/**
 * Description: toggle selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param pins: the selected pin the user need to toggle it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 */
void gpioPinToggle(uint8 port, uint8 pins){
	switch(port){
	case (GPIOA):
		PORTA_DATA ^= pins;
		break;
	case (GPIOB):
		PORTB_DATA ^= pins;
		break;
	case (GPIOC):
		PORTC_DATA ^= pins;
		break;
	case (GPIOD):
		PORTD_DATA ^= pins;
		break;
	default: // PORTA
		PORTA_DATA ^= pins;
		break;
	}
}

/**
 * Description: read selected pin (only one pin) direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param pin: the selected pin the user need to read it's value and takes
 * 				only one member from the enum EN_bits:
 * 				- BIT0
 * 				- BIT1
 * 				- BIT2
 * 				- BIT3
 * 				- BIT4
 * 				- BIT5
 * 				- BIT6
 * 				- BIT7
 * @return
 */
uint8 gpioPinRead(uint8 port, uint8 pin){
	switch(port){
	case (GPIOA):
		return (PORTA_PIN & pin);
		break;
	case (GPIOB):
		return (PORTB_PIN & pin);
		break;
	case (GPIOC):
		return (PORTC_PIN & pin);
		break;
	case (GPIOD):
		return (PORTD_PIN & pin);
		break;
	default: // PORTA
		return (PORTA_PIN & pin);
		break;
	}
}

/*===========================Upper Nibble Control===============================*/
/**
 * Description: set the upper nibble direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param direction
 */
void gpioUpperNibbleDirection(uint8 port, uint8 direction){
	switch(port){
	case (GPIOA):
		PORTA_DIR |= (direction & 0xF0);
		break;
	case (GPIOB):
		PORTB_DIR |= (direction & 0xF0);
		break;
	case (GPIOC):
		PORTC_DIR |= (direction & 0xF0);
		break;
	case (GPIOD):
		PORTD_DIR |= (direction & 0xF0);
		break;
	default: // PORTA
		PORTA_DIR |= (direction & 0xF0);
		break;
	}
}

/**
 * Description: write the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value
 */
void gpioUpperNibbleWrite(uint8 port, uint8 value){
	value <<= 4;
	switch(port){
	case (GPIOA):
		PORTA_DATA &= ~(0xF0);
		PORTA_DATA |= (value & 0xF0);
		break;
	case (GPIOB):
		PORTB_DATA &= ~(0xF0);
		PORTB_DATA |= (value & 0xF0);
		break;
	case (GPIOC):
		PORTC_DATA &= ~(0xF0);
		PORTC_DATA |= (value & 0xF0);
		break;
	case (GPIOD):
		PORTD_DATA &= ~(0xF0);
		PORTD_DATA |= (value & 0xF0);
		break;
	default: // PORTA
		PORTA_DATA &= ~(0xF0);
		PORTA_DATA |= (value & 0xF0);
		break;
	}
}

/**
 * Description: toggle the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 */
void gpioUpperNibbleToggle(uint8 port){
	switch(port){
	case (GPIOA):
		PORTA_DATA ^= 0xF0;
		break;
	case (GPIOB):
		PORTB_DATA ^= 0xF0;
		break;
	case (GPIOC):
		PORTC_DATA ^= 0xF0;
		break;
	case (GPIOD):
		PORTD_DATA ^= 0xF0;
		break;
	default: // PORTA
		PORTA_DATA ^= 0xF0;
		break;
	}
}

/**
 * Description: read the upper nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioUpperNibbleRead(uint8 port){
	switch(port){
	case (GPIOA):
		return (PORTA_PIN & 0xF0);
		break;
	case (GPIOB):
		return (PORTB_PIN & 0xF0);
		break;
	case (GPIOC):
		return (PORTC_PIN & 0xF0);
		break;
	case (GPIOD):
		return (PORTD_PIN & 0xF0);
		break;
	default: // PORTA
		return (PORTA_PIN & 0xF0);
		break;
	}
}

/*===========================Lower Nibble Control===============================*/
/**
 * Description: set the lower nibble direction
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 * @param direction
 */
void gpioLowerNibbleDirection(uint8 port, uint8 direction){
	switch(port){
	case (GPIOA):
		PORTA_DIR |= (direction & 0x0F);
		break;
	case (GPIOB):
		PORTB_DIR |= (direction & 0x0F);
		break;
	case (GPIOC):
		PORTC_DIR |= (direction & 0x0F);
		break;
	case (GPIOD):
		PORTD_DIR |= (direction & 0x0F);
		break;
	default: // PORTA
		PORTA_DIR |= (direction & 0x0F);
		break;
	}
}

/**
 * Description: write the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @param value
 */
void gpioLowerNibbleWrite(uint8 port, uint8 value){
	switch(port){
	case (GPIOA):
		PORTA_DATA &= ~(0x0F);
		PORTA_DATA |= (value & 0x0F);
		break;
	case (GPIOB):
		PORTB_DATA &= ~(0x0F);
		PORTB_DATA |= (value & 0x0F);
		break;
	case (GPIOC):
		PORTC_DATA &= ~(0x0F);
		PORTC_DATA |= (value & 0x0F);
		break;
	case (GPIOD):
		PORTD_DATA &= ~(0x0F);
		PORTD_DATA |= (value & 0x0F);
		break;
	default: // PORTA
		PORTA_DATA &= ~(0x0F);
		PORTA_DATA |= (value & 0x0F);
		break;
	}
}

/**
 * Description: toggle the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 *
 */
void gpioLowerNibbleToggle(uint8 port){
	switch(port){
	case (GPIOA):
		PORTA_DATA ^= 0x0F;
		break;
	case (GPIOB):
		PORTB_DATA ^= 0x0F;
		break;
	case (GPIOC):
		PORTC_DATA ^= 0x0F;
		break;
	case (GPIOD):
		PORTD_DATA ^= 0x0F;
		break;
	default: // PORTA
		PORTA_DATA ^= 0x0F;
		break;
	}
}

/**
 * Description: read the lower nibble value
 * @param port: portID and takes the following values
 * 				- 0 -> GPIOA
 * 				- 1 -> GPIOB
 * 				- 2 -> GPIOC
 * 				- 3 -> GPIOD
 * @return
 */
uint8 gpioLowerNibbleRead(uint8 port){
	switch(port){
	case (GPIOA):
		return (PORTA_PIN & 0x0F);
		break;
	case (GPIOB):
		return (PORTB_PIN & 0x0F);
		break;
	case (GPIOC):
		return (PORTC_PIN & 0x0F);
		break;
	case (GPIOD):
		return (PORTD_PIN & 0x0F);
		break;
	default: // PORTA
		return (PORTA_PIN & 0x0F);
		break;
	}
}
