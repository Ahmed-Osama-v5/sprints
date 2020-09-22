/*
 * softwareDelay.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef SOFTWAREDELAY_H_
#define SOFTWAREDELAY_H_

#include "std_types.h"

/**
 * @brief this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param __ms: the milli-seconds
 */
void SwDelay_ms(double __ms);

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the micro-seconds
 */
void SwDelay_us(double __us);

#endif /* SOFTWAREDELAY_H_ */
