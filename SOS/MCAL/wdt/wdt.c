/*
 * wdt.c
 *
 *  Created on: Jan 18, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "wdt.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
void WDT_Config(uint8 u8_prescaler)
{

  switch (u8_prescaler)
  {
    case (WDT_PRESCALER_16K):
      WDTCR |= WDE;
      break;
    case (WDT_PRESCALER_32K):
      WDTCR |= (WDE | WDP0);
      break;
    case (WDT_PRESCALER_64K):
      WDTCR |= (WDE | WDP1);
      break;
    case (WDT_PRESCALER_128K):
      WDTCR |= (WDE | WDP1 | WDP0);
      break;
    case (WDT_PRESCALER_256K):
      WDTCR |= (WDE | WDP2);
      break;
    case (WDT_PRESCALER_512K):
      WDTCR |= (WDE | WDP2 | WDP0);
      break;
    case (WDT_PRESCALER_1024K):
      WDTCR |= (WDE | WDP2 | WDP1);
      break;
    case (WDT_PRESCALER_2048K):
      WDTCR |= (WDE | WDP2 | WDP1 | WDP0);
      break;
    default:
      break;
  }

  //WDTCR |= WDE;
}

void WDT_Enable(void)
{
  WDTCR |= WDE;
}

void WDT_Off(void)
{
  /* reset WDT */
  asm("wdr");

  /* Write logical one to WDTOE and WDE */
  WDTCR |= (WDTOE | WDE);

  /* Turn off WDT */
  WDTCR = 0x00;
}
