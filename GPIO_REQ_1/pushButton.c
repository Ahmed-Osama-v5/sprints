/*
 * pushButton.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Ahmed Osama
 */

#include "std_types.h"
#include "gpio.h"
#include "pushButton.h"

/**
 * Description: Initialize the BTN_x Pin state (where x 0, 1, 2, 3) to Input
 * @param btn_id: The btn to be initialized and it takes
 * 				  one of the enum (En_buttonId) parameters
 *
 */
void pushButton_Init(En_buttonId btn_id){
	switch(btn_id){
	case(BTN_0):
		gpioPinDirection(BTN_0_GPIO, BTN_0_BIT, INPUT);
		break;
	case(BTN_1):
		gpioPinDirection(BTN_1_GPIO, BTN_1_BIT, INPUT);
		break;
	case(BTN_2):
		gpioPinDirection(BTN_2_GPIO, BTN_2_BIT, INPUT);
		break;
	case(BTN_3):
		gpioPinDirection(BTN_3_GPIO, BTN_3_BIT, INPUT);
		break;
	}
}
/**
 * Description: read all BTN_x (where x 0, 1, 2, 3) states and store it in the program
 *
 * @note : this function must be called in the system tick handler or in the super loop handler
 */
void pushButton_Update(void){

}
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id){
	switch(btn_id){
	case(BTN_0):
		//return gpioPinRead(BTN_0_GPIO, BTN_0_BIT);
		break;
	}
}
