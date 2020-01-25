/*
 * keypad_Cfg.h
 *
 *  Created on: Jan 20, 2020
 *      Author: Ahmed Osama
 */

#ifndef ECUAL_KEYPAD_KEYPAD_CFG_H_
#define ECUAL_KEYPAD_KEYPAD_CFG_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"

/*- CONSTANTS ----------------------------------------------*/
/* Keypad layout */
/* 3x3 keypad */
#define KEYPAD_COL_COUNT	(3)
#define KEYPAD_ROW_COUNT	(3)

/* 4x4 keypad */
/*
#define KEYPAD_COL_COUNT	(4)
#define KEYPAD_ROW_COUN		(4)
*/

/* Keypad pins */
#define KEYPAD_ROW_ZERO_GPIO  	GPIOC
#define KEYPAD_ROW_ZERO_PIN		PIN2

#define KEYPAD_ROW_ONE_GPIO  	GPIOC
#define KEYPAD_ROW_ONE_PIN		PIN3

#define KEYPAD_ROW_TWO_GPIO  	GPIOC
#define KEYPAD_ROW_TWO_PIN		PIN4

#define KEYPAD_COL_ZERO_GPIO  	GPIOC
#define KEYPAD_COL_ZERO_PIN		PIN5

#define KEYPAD_COL_ONE_GPIO  	GPIOC
#define KEYPAD_COL_ONE_PIN		PIN6

#define KEYPAD_COL_TWO_GPIO  	GPIOC
#define KEYPAD_COL_TWO_PIN		PIN7

#if (KEYPAD_COL_COUNT == 4)
#define KEYPAD_COL_THREE_GPIO  	GPIOC
#define KEYPAD_ROW_THREE_PIN	PIN2
#endif // KEYPAD_COL_COUNT

#if (KEYPAD_ROW_COUNT == 4)
#define KEYPAD_ROW_THREE_GPIO  	GPIOC
#define KEYPAD_ROW_THREE_PIN	PIN2
#endif // KEYPAD_COL_COUNT


/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8* ptrkey_t;

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/


#endif /* ECUAL_KEYPAD_KEYPAD_CFG_H_ */
