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
/**
 * @brief Debounce button
 * @param mask
 * @return (1) if button is pressed,
 * 		   (0) if button is not pressed
 */
uint8 debounce(uint8 u8_GPIO, uint8 u8_Pin);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint8 gu8_KeypadInitState = NOT_INITIALIZED;
static uint8 gu8_KeypadDebounceOnes = 0, gu8_KeypadDebounceZeros = 1;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/**
 * @brief Debounce button
 * @param mask
 * @return (1) if button is pressed,
 * 		   (0) if button is not pressed
 */
uint8 debounce(uint8 u8_GPIO, uint8 u8_Pin)
{
	//uint8 u8_retVal, u8_DioReadResult;
	//DIO_Read(u8_GPIO, u8_Pin, &u8_DioReadResult);
//	if(u8_DioReadResult == LOW)
//	{
//		if(gu8_KeypadDebounceZeros >= 100)
//		{
//			gu8_KeypadDebounceZeros = 0;
//			u8_retVal = 1;
//		}
//		else
//		{
//			gu8_KeypadDebounceZeros++;
//			u8_retVal = 0;
//		}
//	}
//	else
//	{
//		/* Do nothing */
//	}
//	return u8_retVal;

	  uint8 u8_i, u8_DioReadResult;
	  for(u8_i=0;u8_i<70;u8_i++)
	  {
		  DIO_Read(u8_GPIO, u8_Pin, &u8_DioReadResult);
		  /* Check if Input is LOW */

		  if(u8_DioReadResult == HIGH)
		  {
			  gu8_KeypadDebounceOnes++;
		  }
		  else
		  {
			  gu8_KeypadDebounceZeros++;
		  }
	  }
	  return (gu8_KeypadDebounceOnes < gu8_KeypadDebounceZeros);

}

/*- APIs IMPLEMENTATION -----------------------------------*/
/**
 * @brief Initialize the keypad
 * @param void
 * @return Error code
 */
sint8 KeyPad_init(void)
{
  sint8 retval = KEYPAD_BASE_ERROR + SUCCESS;

  if(gu8_KeypadInitState == INITIALIZED)
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

	  /* Output LOW on all rows */
	  DIO_Write(KEYPAD_ROW_ZERO_GPIO, KEYPAD_ROW_ZERO_PIN, LOW);
	  DIO_Write(KEYPAD_ROW_ONE_GPIO, KEYPAD_ROW_ONE_PIN, LOW);
	  DIO_Write(KEYPAD_ROW_TWO_GPIO, KEYPAD_ROW_TWO_PIN, LOW);
#if (KEYPAD_ROW_COUNT == 4)
	  DIO_Write(KEYPAD_ROW_THREE_GPIO, KEYPAD_ROW_THREE_PIN, LOW);
#endif

	  /* Configure COL0 */
	  strDio_Cfg_s.GPIO = KEYPAD_COL_ZERO_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_COL_ZERO_PIN;
	  strDio_Cfg_s.dir = INPUT;

	  /* Initialize COL0 */
	  DIO_init(&strDio_Cfg_s);

	  /* Configure COL1 */
	  strDio_Cfg_s.GPIO = KEYPAD_COL_ONE_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_COL_ONE_PIN;
	  strDio_Cfg_s.dir = INPUT;

	  /* Initialize COL1 */
	  DIO_init(&strDio_Cfg_s);

	  /* Configure COL2 */
	  strDio_Cfg_s.GPIO = KEYPAD_COL_TWO_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_COL_TWO_PIN;
	  strDio_Cfg_s.dir = INPUT;

	  /* Initialize COL2 */
	  DIO_init(&strDio_Cfg_s);

  #if (KEYPAD_COL_COUNT == 4)

	  /* Configure COL3 */
	  strDio_Cfg_s.GPIO = KEYPAD_COL_THREE_GPIO;
	  strDio_Cfg_s.pins = KEYPAD_COL_THREE_PIN;
	  strDio_Cfg_s.dir = INPUT;

	  /* Initialize COL3 */
	  DIO_init(&strDio_Cfg_s);
  #endif

	  /* Activate internal pull-up resistors on all columns */
	  /*
	  DIO_Write(KEYPAD_COL_ZERO_GPIO, KEYPAD_COL_ZERO_PIN, HIGH);
	  DIO_Write(KEYPAD_COL_ONE_GPIO, KEYPAD_COL_ONE_PIN, HIGH);
	  DIO_Write(KEYPAD_COL_TWO_GPIO, KEYPAD_COL_TWO_PIN, HIGH);
  #if (KEYPAD_COL_COUNT == 4)
	  DIO_Write(KEYPAD_COL_THREE_GPIO, KEYPAD_COL_THREE_PIN, HIGH);
  #endif
  */

	  /* Set initState */
	  gu8_KeypadInitState = INITIALIZED;
  }
  return retval;
}

/**
 * @brief read the value stored in a global variable
 *        and output pressed key through a pointer
 * @param ptr_key pointer to integer variable which store the pressed key number
 * @return Error code
 */
void KeyPad_getPressedKey(uint8 *ptr_key)
{
	uint8 u8_DioReadResult;
	/* Set Row0 HIGH */
		DIO_Write(KEYPAD_ROW_ZERO_GPIO, KEYPAD_ROW_ZERO_PIN, HIGH);
		/* Set Row1 LOW */
		DIO_Write(KEYPAD_ROW_ONE_GPIO, KEYPAD_ROW_ONE_PIN, LOW);
		/* Set Row2 LOW */
		DIO_Write(KEYPAD_ROW_TWO_GPIO, KEYPAD_ROW_TWO_PIN, LOW);

		/* Scan Col0 */
		DIO_Read(KEYPAD_COL_ZERO_GPIO, KEYPAD_COL_ZERO_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 1 is pressed */
			*ptr_key = ONE;
		}
		else
		{
			/* No key is pressed */
			*ptr_key = NO_KEY_PRESSED;
		}
		/* Scan Col1 */
		DIO_Read(KEYPAD_COL_ONE_GPIO, KEYPAD_COL_ONE_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 2 is pressed */
			*ptr_key = TWO;
		}
		else
		{
			/* Do nothing */
		}
		/* Scan Col2 */
		DIO_Read(KEYPAD_COL_TWO_GPIO, KEYPAD_COL_TWO_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 3 is pressed */
			*ptr_key = THREE;
		}
		else
		{
			/* Do nothing */
		}


		/* Set Row0 LOW */
		DIO_Write(KEYPAD_ROW_ZERO_GPIO, KEYPAD_ROW_ZERO_PIN, LOW);
		/* Set Row1 HIGH */
		DIO_Write(KEYPAD_ROW_ONE_GPIO, KEYPAD_ROW_ONE_PIN, HIGH);
		/* Set Row2 LOW */
		DIO_Write(KEYPAD_ROW_TWO_GPIO, KEYPAD_ROW_TWO_PIN, LOW);

		/* Scan Col0 */
		DIO_Read(KEYPAD_COL_ZERO_GPIO, KEYPAD_COL_ZERO_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 4 is pressed */
			*ptr_key = FOUR;
		}
		else
		{
			/* Do nothing */
		}
		/* Scan Col1 */
		DIO_Read(KEYPAD_COL_ONE_GPIO, KEYPAD_COL_ONE_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 5 is pressed */
			*ptr_key = FIVE;
		}
		else
		{
			/* Do nothing */
		}
		/* Scan Col2 */
		DIO_Read(KEYPAD_COL_TWO_GPIO, KEYPAD_COL_TWO_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 6 is pressed */
			*ptr_key = SIX;
		}
		else
		{
			/* Do nothing */
		}


		/* Set Row0 LOW */
		DIO_Write(KEYPAD_ROW_ZERO_GPIO, KEYPAD_ROW_ZERO_PIN, LOW);
		/* Set Row1 LOW */
		DIO_Write(KEYPAD_ROW_ONE_GPIO, KEYPAD_ROW_ONE_PIN, LOW);
		/* Set Row2 HIGH */
		DIO_Write(KEYPAD_ROW_TWO_GPIO, KEYPAD_ROW_TWO_PIN, HIGH);

		/* Scan Col0 */
		DIO_Read(KEYPAD_COL_ZERO_GPIO, KEYPAD_COL_ZERO_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 7 is pressed */
			*ptr_key = SEVEN;
		}
		else
		{
			/* Do nothing */
		}
		/* Scan Col1 */
		DIO_Read(KEYPAD_COL_ONE_GPIO, KEYPAD_COL_ONE_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 8 is pressed */
			*ptr_key = EIGHT;
		}
		else
		{
			/* Do nothing */
		}
		/* Scan Col2 */
		DIO_Read(KEYPAD_COL_TWO_GPIO, KEYPAD_COL_TWO_PIN, &u8_DioReadResult);
		if(u8_DioReadResult == HIGH)
		{
			/* Key 9 is pressed */
			*ptr_key = NINE;
		}
		else
		{
			/* Do nothing */
		}

		/* ~ 15 uS delay */
		/* 240 * 62.5 nS = 15 uS */
		uint8 x;
		for(x=0;x<240;x++)
		{
			asm("nop");
		}
}
