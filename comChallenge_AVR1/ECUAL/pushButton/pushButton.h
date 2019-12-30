/*
 * pushButton.h
 *
 *  Created on: Dec 29, 2019
 *      Author: Ahmed
 */

#ifndef ECUAL_PUSHBUTTON_PUSHBUTTON_H_
#define ECUAL_PUSHBUTTON_PUSHBUTTON_H_

#include "std_types.h"
#include "dio.h"

#include "pushButtonConfig.h"
#include "softwareDelay.h"

typedef enum En_buttonId{
	BTN_0,
	BTN_1,
	BTN_2,
	BTN_3
}En_buttonId;

typedef enum En_buttonStatus_t{
	Released,
	Prepressed,
	Pressed,
	Prereleased

}En_buttonStatus_t;

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
 * @note : this function must be called in the system tick handler or in the super loop handler
 */
void pushButton_Update(void);
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id);

#endif /* ECUAL_PUSHBUTTON_PUSHBUTTON_H_ */
