/*
 * pushButton.c
 *
 *  Created on: Dec 7, 2019
 *      Author: Omar Zayed
 */

#include "DIO.h"
#include "pushButton.h"

static buttons avrbuttons[BTN_MAX_NUM];
static uint8 buttonNo = 0;

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */

void pushButton_Init(En_buttonId btn_id)
{
	avrbuttons[buttonNo].buttonID = btn_id;
	DIO_Cfg_s DIO_Cfg;
	switch (btn_id)
	{
	case BTN_0:
		DIO_Cfg.GPIO = BTN_0_GPIO;
		DIO_Cfg.pins = BTN_0_BIT;
		DIO_Cfg.dir = INPUT;
		DIO_init(&DIO_Cfg);
		avrbuttons[buttonNo].GPIOPort = BTN_0_GPIO;
		avrbuttons[buttonNo].buttonBit = BTN_0_BIT;
		break;
	case BTN_1:
		DIO_Cfg.GPIO = BTN_1_GPIO;
		DIO_Cfg.pins = BTN_1_BIT;
		DIO_Cfg.dir = INPUT;
		DIO_init(&DIO_Cfg);
		avrbuttons[buttonNo].GPIOPort = BTN_1_GPIO;
		avrbuttons[buttonNo].buttonBit = BTN_1_BIT;
		break;
	default:
		break;
	}
	buttonNo++;

}

/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick hundler or in the super loop hundler
 */
void pushButton_Update(void)
{
	uint8 READData;
	for (uint8 i = 0; i < buttonNo; i++)
	{

		DIO_Read(avrbuttons[i].GPIOPort, avrbuttons[i].buttonBit, &READData);
		if (READData == avrbuttons[i].buttonBit)
		{
			if (avrbuttons[i].buttonStatus == Released)
			{
				avrbuttons[i].buttonStatus = Prepressed;
			}
			else if (avrbuttons[i].buttonStatus == Prepressed)
			{
				avrbuttons[i].buttonStatus = Pressed;
			}
		}
		else
		{
			if (avrbuttons[i].buttonStatus == Pressed)
			{
				avrbuttons[i].buttonStatus = Prereleased;
			}
			else if (avrbuttons[i].buttonStatus == Prereleased)
			{
				avrbuttons[i].buttonStatus = Released;
			}
		}
	}
}
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id)
{
	En_buttonStatus_t outStatus;
	for (uint8 i = 0; i < buttonNo; i++)
	{
		if (btn_id == avrbuttons[i].buttonID)
		{
			outStatus = avrbuttons[i].buttonStatus;
		}
	}

	return outStatus;

}

