/*
 * HwPWM.h
 *
 *  Created on: Oct 28, 2019
 *      Author: Sprints
 */

#ifndef HWPWM_H_
#define HWPWM_H_

#include "timers.h"

void HwPWM_Init(void);
void HwPWM_ChangeWidth(uint8 duty, uint32 frequency);
#endif /* HWPWM_H_ */
