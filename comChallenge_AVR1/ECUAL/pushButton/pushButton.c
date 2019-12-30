/*
 * pushButton.c
 *
 *  Created on: Dec 29, 2019
 *      Author: Ahmed
 */

#include "pushButton.h"


#include "std_types.h"
#include "pushButton.h"
#include "softwareDelay.h"

static uint8 gsu8_buttonGpioArr[BTN_MAX_NUM] = {0};
static uint8 gsu8_buttonPinArr[BTN_MAX_NUM] = {0};
static uint8 gsu8_buttonStateArr[BTN_MAX_NUM] = {0};

static void pushButtonMapping(void){
	gsu8_buttonGpioArr[0] = BTN_0_GPIO;
	gsu8_buttonGpioArr[1] = BTN_1_GPIO;

	gsu8_buttonPinArr[0] = BTN_0_BIT;
	gsu8_buttonPinArr[1] = BTN_1_BIT;
}

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
void pushButton_Init(En_buttonId btn_id){
	pushButtonMapping();
	DIO_Cfg_s str_DIO_s = {0}; /* Dio configuration struct */
	switch(btn_id){
	case(BTN_0):
		str_DIO_s.GPIO = BTN_0_GPIO;
		str_DIO_s.dir = INPUT;
		str_DIO_s.pins = BTN_0_BIT;
		DIO_init(&str_DIO_s);
		break;
	case(BTN_1):
		str_DIO_s.GPIO = BTN_1_GPIO;
		str_DIO_s.dir = INPUT;
		str_DIO_s.pins = BTN_1_BIT;
		DIO_init(&str_DIO_s);
		break;
	case(BTN_2):
		str_DIO_s.GPIO = BTN_2_GPIO;
		str_DIO_s.dir = INPUT;
		str_DIO_s.pins = BTN_2_BIT;
		DIO_init(&str_DIO_s);
		break;
	case(BTN_3):
		str_DIO_s.GPIO = BTN_3_GPIO;
		str_DIO_s.dir = INPUT;
		str_DIO_s.pins = BTN_3_BIT;
		DIO_init(&str_DIO_s);
		break;
	}
}
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 */
void pushButton_Update(void){

	uint8 data = 0;
	DIO_Read(BTN_0_GPIO, BTN_0_BIT, &data);

	if(data)
	{
		gsu8_buttonStateArr[BTN_0] = Pressed;
	}
	else
	{
		gsu8_buttonStateArr[BTN_0] = Released;
	}

	DIO_Read(BTN_1_GPIO, BTN_1_BIT, &data);
	if(data)
	{
		gsu8_buttonStateArr[BTN_1] = Pressed;
	}
	else
	{
		gsu8_buttonStateArr[BTN_1] = Released;
	}

	DIO_Read(BTN_2_GPIO, BTN_2_BIT, &data);
	if(data)
	{
		gsu8_buttonStateArr[BTN_2] = Pressed;
	}
	else
	{
		gsu8_buttonStateArr[BTN_2] = Released;
	}

	DIO_Read(BTN_3_GPIO, BTN_3_BIT, &data);
	if(data)
	{
		gsu8_buttonStateArr[BTN_3] = Pressed;
	}
	else
	{
		gsu8_buttonStateArr[BTN_3] = Released;
	}
	SwDelay_ms(300);
}
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id){
	return gsu8_buttonStateArr[btn_id];
}
