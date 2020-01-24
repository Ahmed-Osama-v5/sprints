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
#define ZERO            (0)
#define ONE             (1)
#define TWO             (2)
#define THREE           (3)
#define FOUR            (4)
#define FIVE            (5)
#define SIX             (6)
#define SEVEN           (7)
#define EIGHT           (8)
#define NINE            (9)

//KEY_ZERO + KEY_ONE

#define KEY_ZERO       	(0x00)
#define KEY_ONE         (0x01)
#define KEY_TWO         (0x02)
#define KEY_THREE       (0x04)
#define KEY_FOUR        (0x08)
#define KEY_FIVE       	(0x10)
#define KEY_SIX         (6)
#define KEY_SEVEN       (7)
#define KEY_EIGHT       (8)
#define KEY_NINE        (9)

#define NO_KEY_PRESSED	(0xFF)

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
 * @brief scans keypad and stores pressed key in a global variable
 * @param void
 * @return Error code
 */
sint8 KeyPad_update(void);

/**
 * @brief read the value stored in a global variable
 *        and output pressed key through a pointer
 * @param ptr_key pointer to integer variable which store the pressed key number
 * @return Error code
 */
sint8 KeyPad_getPressedKey(ptrkey_t ptr_key);

#endif /* ECUAL_KEYPAD_KEYPAD_H_ */
