/*
 * pushButton.c
 *
 *  Created on: Dec 3, 2019
 *      Author: Ahmed Osama
 */

#include "std_types.h"
#include "gpio.h"
#include "pushButton.h"
#include "softwareDelay.h"

En_buttonStatus_t g_pb_0_State = Released;
En_buttonStatus_t g_pb_1_State =  Released;
En_buttonStatus_t g_pb_2_State = Released;
En_buttonStatus_t g_pb_3_State =  Released;

static En_buttonStatus_t g_pb_0_LastState;
static En_buttonStatus_t g_pb_1_LastState;
static En_buttonStatus_t g_pb_2_LastState;
static En_buttonStatus_t g_pb_3_LastState;


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
	g_pb_0_State = pushButton_GetStatus(BTN_0);
	g_pb_1_State = pushButton_GetStatus(BTN_1);
	g_pb_2_State = pushButton_GetStatus(BTN_2);
	g_pb_3_State = pushButton_GetStatus(BTN_3);
}
/**
 * Description: read BTN_x (where x 0, 1, 2, 3) state which is stored in the program
 * 				in the update function
 *
 */
En_buttonStatus_t pushButton_GetStatus(En_buttonId btn_id){
	switch(btn_id){
	case(BTN_0):
		if(gpioPinRead(BTN_0_GPIO, BTN_0_BIT))
			g_pb_0_State = Pressed;
		else
			g_pb_0_State = Released;
		if(g_pb_0_State != g_pb_0_LastState){
			if(g_pb_0_State == HIGH){
				g_pb_0_LastState = g_pb_0_State;
				return Pressed;
			}
			else{
				g_pb_0_LastState = g_pb_0_State;
				return Released;
			}
		}
		break;
	case(BTN_1):
		if(gpioPinRead(BTN_1_GPIO, BTN_1_BIT))
			g_pb_1_State = Pressed;
		else
			g_pb_1_State = Released;
		if(g_pb_1_State != g_pb_1_LastState){
			if(g_pb_0_State == HIGH){
				g_pb_1_LastState = g_pb_1_State;
				return Pressed;
			}
			else{
				g_pb_1_LastState = g_pb_1_State;
				return Released;
			}
		}
		break;
	case(BTN_2):
		if(gpioPinRead(BTN_2_GPIO, BTN_2_BIT))
			g_pb_2_State = Pressed;
		else
			g_pb_2_State = Released;
		if(g_pb_2_State != g_pb_2_LastState){
			if(g_pb_2_State == HIGH){
				g_pb_2_LastState = g_pb_2_State;
				return Pressed;
			}
			else{
				g_pb_2_LastState = g_pb_2_State;
				return Released;
			}
		}
		break;
	case(BTN_3):
		if(gpioPinRead(BTN_3_GPIO, BTN_3_BIT))
			g_pb_3_State = Pressed;
		else
			g_pb_3_State = Released;
		if(g_pb_3_State != g_pb_3_LastState){
			if(g_pb_3_State == HIGH){
				g_pb_3_LastState = g_pb_3_State;
				return Pressed;
			}
			else{
				g_pb_3_LastState = g_pb_3_State;
				return Released;
			}
		}
		break;
	default:
		g_pb_0_State = gpioPinRead(BTN_0_GPIO, BTN_0_BIT);
		if(g_pb_0_State != g_pb_0_LastState){
			if(g_pb_0_State == HIGH){
				g_pb_0_LastState = g_pb_0_State;
				return Pressed;
			}
			else{
				g_pb_0_LastState = g_pb_0_State;
				return Released;
			}
		}
		break;
	}
}
