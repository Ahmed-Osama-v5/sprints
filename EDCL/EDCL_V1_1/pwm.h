/*
 * pwm.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

void PWM0_init();
void PWM0_Stop();
void PWM0_Start();
void PWM0_Set_Duty(unsigned char Duty);
void PWM2_init();
void PWM2_Stop();
void PWM2_Start();
void PWM2_Set_Duty(unsigned char Duty);


#endif /* INC_PWM_H_ */
