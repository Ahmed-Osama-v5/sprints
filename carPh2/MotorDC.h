/*
 * MotorDC.h
 *
 *  Created on: Oct 26, 2019
 *      Author: Sprints
 */

#ifndef MOTORDC_H_
#define MOTORDC_H_
#include "MotorDC_CFG.h"
#include "timers.h"

typedef enum En_motorType_t{
	MOT_1,
	MOT_2
}En_motorType_t;

typedef enum En_motorDir_t{
	STOP,
	FORWARD,
	BACKWARD
}En_motorDir_t;

/**
 * Description: 
 * @param
 */
void MotorDC_Init(En_motorType_t MOT_x);

/**
 * Description: 
 * @param 
 * @param 
 */
void MotorDC_Dir(En_motorType_t MOT_x, En_motorDir_t dir);

/**
 * Description: 
 * @param 
 */
void MotorDC_Speed_PollingWithT0(uint8 speed);

/**
 * Description: set the port value (which is PORT register)
 * @param 
 */
void MotorDC_Speed_HwPWM(uint8 speed);
#endif /* MOTORDC_H_ */
