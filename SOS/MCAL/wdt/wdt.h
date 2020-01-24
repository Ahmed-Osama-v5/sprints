/*
 * wdt.h
 *
 *  Created on: Jan 18, 2020
 *      Author: Ahmed Osama
 */

#ifndef MCAL_WDT_WDT_H_
#define MCAL_WDT_WDT_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"
#include "registers.h"

/*- CONSTANTS ----------------------------------------------*/
#define		WDT_PRESCALER_16K      (0)
#define		WDT_PRESCALER_32K      (1)
#define		WDT_PRESCALER_64K      (2)
#define		WDT_PRESCALER_128K     (3)
#define		WDT_PRESCALER_256K     (4)
#define		WDT_PRESCALER_512K     (5)
#define		WDT_PRESCALER_1024K    (6)
#define		WDT_PRESCALER_2048K    (7)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

void WDT_Config(uint8 prescaler);
void WDT_Enable(void);
void WDT_Off(void);

#endif /* MCAL_WDT_WDT_H_ */
