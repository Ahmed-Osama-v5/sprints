/*
 * keypad.h
 *
 *  Created on: Jan 20, 2020
 *      Author: Ahmed Osama
 */

#ifndef ECUAL_KEYPAD_KEYPAD_H_
#define ECUAL_KEYPAD_KEYPAD_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"
#include "dio.h"
#include "system_ErrorHandling.h"
#include "retval.h"
#include "keypad_Cfg.h"

/*- CONSTANTS ----------------------------------------------*/

/* Values returned by keypad module */
#define ONE             (1U)
#define TWO             (2U)
#define THREE           (3U)
#define FOUR            (4U)
#define FIVE            (5U)
#define SIX             (6U)
#define SEVEN           (7U)
#define EIGHT           (8U)
#define NINE            (9U)

#define NO_KEY_PRESSED	(0xFFU)

/*  */

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/**
 * @brief Initialize the keypad
 * @param void
 * @return Error code
 */
sint8 KeyPad_init(void);

/**
 * @brief read the value stored in a global variable
 *        and output pressed key through a pointer
 * @param ptr_key pointer to integer variable which store the pressed key number
 * @return void
 */
void KeyPad_getPressedKey(uint8 *ptr_key);

#endif /* ECUAL_KEYPAD_KEYPAD_H_ */
