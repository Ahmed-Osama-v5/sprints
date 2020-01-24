/*
 * keypad.c
 *
 *  Created on: Jan 20, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "keypad.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint8 gu8_keypadInitState = NOT_INITIALIZED;
static uint8 gu8_KeypadPressedKey = NO_KEY_PRESSED;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
/**
 * @brief Initialize the keypad
 * @param void
 * @return Error code
 */
sint8 KeyPad_init(void)
{
  sint8 retval = KEYPAD_BASE_ERROR + SUCCESS;

  if(gu8_keypadInitState == INITIALIZED)
  {
	  retval = KEYPAD_BASE_ERROR + ERROR_NOT_INITIALIZED;
  }
  else
  {
	  /* Initialize ROWs and COLs */
	  /* Create instance of DIO_Cfg_S */
	  DIO_Cfg_s strDio_Cfg_s = {0};

	  /* Configure ROW0 */
	  strDio_Cfg_s.GPIO = KEYPAD_ROW_ZERO_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_ROW_ZERO_PIN;
	  strDio_Cfg_s.dir = OUTPUT;

	  /* Initialize ROW0 */
	  DIO_init(&strDio_Cfg_s);

	  /* Configure ROW1 */
	  strDio_Cfg_s.GPIO = KEYPAD_ROW_ONE_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_ROW_ONE_PIN;
	  strDio_Cfg_s.dir = OUTPUT;

	  /* Initialize ROW1 */
	  DIO_init(&strDio_Cfg_s);

	  /* Configure ROW2 */
	  strDio_Cfg_s.GPIO = KEYPAD_ROW_TWO_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_ROW_TWO_PIN;
	  strDio_Cfg_s.dir = OUTPUT;

	  /* Initialize ROW2 */
	  DIO_init(&strDio_Cfg_s);

#if (KEYPAD_ROW_COUNT == 4)

	  /* Configure ROW3 */
	  strDio_Cfg_s.GPIO = KEYPAD_ROW_THREE_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_ROW_THREE_PIN;
	  strDio_Cfg_s.dir = OUTPUT;

	  /* Initialize ROW3 */
	  DIO_init(&strDio_Cfg_s);
#endif

	  /* Configure COL0 */
	  strDio_Cfg_s.GPIO = KEYPAD_COL_ZERO_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_COL_ZERO_PIN;
	  strDio_Cfg_s.dir = OUTPUT;

	  /* Initialize COL0 */
	  DIO_init(&strDio_Cfg_s);

	  /* Configure COL1 */
	  strDio_Cfg_s.GPIO = KEYPAD_COL_ONE_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_COL_ONE_PIN;
	  strDio_Cfg_s.dir = OUTPUT;

	  /* Initialize COL1 */
	  DIO_init(&strDio_Cfg_s);

	  /* Configure COL2 */
	  strDio_Cfg_s.GPIO = KEYPAD_COL_TWO_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_COL_TWO_PIN;
	  strDio_Cfg_s.dir = OUTPUT;

	  /* Initialize COL2 */
	  DIO_init(&strDio_Cfg_s);

  #if (KEYPAD_COL_COUNT == 4)

	  /* Configure COL3 */
	  strDio_Cfg_s.GPIO = KEYPAD_COL_THREE_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_COL_THREE_PIN;
	  strDio_Cfg_s.dir = OUTPUT;

	  /* Initialize COL3 */
	  DIO_init(&strDio_Cfg_s);
  #endif

	  /* Set initState */
	  gu8_keypadInitState = INITIALIZED;
  }
  return retval;
}

/**
 * @brief scans keypad and stores pressed key in a global variable
 * @param void
 * @return Error code
 */
sint8 KeyPad_update(void)
{
	sint8 retval = KEYPAD_BASE_ERROR + SUCCESS;

	if(gu8_keypadInitState == NOT_INITIALIZED)
	{
		retval = KEYPAD_BASE_ERROR + ERROR_NOT_INITIALIZED;
	}
	else
	{

	}
	return retval;
}

/**
 * @brief read the value stored in a global variable
 *        and output pressed key through a pointer
 * @param ptr_key pointer to integer variable which store the pressed key number
 * @return Error code
 */
sint8 KeyPad_getPressedKey(ptrkey_t ptr_key)
{
	sint8 retval = KEYPAD_BASE_ERROR + SUCCESS;

	if(gu8_keypadInitState == NOT_INITIALIZED)
	{
		retval = KEYPAD_BASE_ERROR + ERROR_NOT_INITIALIZED;
	}
	else
	{
		/* Output pressed key */
		*ptr_key = gu8_KeypadPressedKey;
	}
	return retval;
}
