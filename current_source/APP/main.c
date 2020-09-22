/*
 * main.c
 *
 *  Created on: Aug 31, 2020
 *      Author: Ahmed Osama
 * Contact: eng.a.osama92@gmail.com
 */

/*- INCLUDES ----------------------------------------------*/
#include "registers.h"
#include "dio.h"
#include "softwareDelay.h"
#include "pwm.h"
#include "pushButton.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/

int main(void)
{
	Pwm_Cfg_s_t str_Pwm = {0};
	str_Pwm.channel = PWM_CH1A;
	str_Pwm.prescaler = PWM_PRESCALER_NO;
	Pwm_Init(&str_Pwm);
	Pwm_Start(PWM_CH1A, 2, 10000);

	uint8 i = 0;
	while(1)
	{
		for(i=1;i<45;i++)
		{
			Pwm_Update(PWM_CH1A, i, 10000);
			SwDelay_ms(5000);
		}
	}
	return 0;
}
