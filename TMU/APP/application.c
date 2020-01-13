/*
 * application.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed
 */
/*- INCLUDES ----------------------------------------------*/
#include "std_types.h"
#include "tmu.h"
#include "interrupt.h"
#include "sleep.h"
#include "dio.h"
#include "softwareDelay.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
void LED3_Toggle(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static sint8 gsi8_TMU_retval;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
int main(void)
{
  /* Create instance of  DIO_Cfg_s and initialize it with zeros*/
  DIO_Cfg_s str_DIO_Cfg_s = {0};

  /* Configure LED3 pin as digital output */
  str_DIO_Cfg_s.GPIO = GPIOB;
  str_DIO_Cfg_s.dir = OUTPUT;
  str_DIO_Cfg_s.pins = PIN7;

  /* Initialize LED3 pin */
  DIO_init(&str_DIO_Cfg_s);

  /* Turn-off LED3 */
  DIO_Write(GPIOB, PIN7, LOW);

  gsi8_TMU_retval = TMU_Init();
  /* Enable interrupts */
  sei();
  gsi8_TMU_retval = TMU_Start();
  /* Enter Idle sleep mode */
  cpu_Sleep(IDLE);
    while(1)
    {
	/* Toggle LED3 */
	DIO_Toggle(GPIOB, PIN7);
	SwDelay_ms(500);
    }
    return 0;
}
