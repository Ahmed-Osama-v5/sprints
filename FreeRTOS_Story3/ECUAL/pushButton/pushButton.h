/*
 * pushButton.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

//#define F_CPU			(16000000)
#include "pushButtonConfig.h"
#include <util/delay.h>
#include "std_types.h"

typedef enum En_buttonId{
	BTN_0,
	BTN_1,
}En_buttonId;

typedef enum En_buttonStatus_t{
	Released,
	Prepressed,
	Pressed,
	Prereleased

}En_buttonStatus_t;

typedef struct buttons
{
	En_buttonId buttonID;
	uint8 GPIOPort;
	uint8 buttonBit;
	En_buttonStatus_t buttonStatus;

}buttons;

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
void pushButton_Init(En_buttonId btn_id);
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick hundler or in the super loop hundler
 */
void pushButton_Update(void);
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id);

#endif /* PUSHBUTTON_H_ */
