/*
 * application.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */
/*- INCLUDES ----------------------------------------------*/
#include "std_types.h"
#include "tmu.h"
#include "interrupt.h"
#include "sleep.h"
#include "dio.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/**
* @brief: LED2 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED2_Toggle(void);

/**
* @brief: LED2 Delay Callback
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED2_DelayComplete(void);

/**
* @brief: LED2 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED3_Toggle(void);

/**
* @brief: LED3 Delay Callback
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED3_DelayComplete(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static sint8 gsi8_TMU_retval;
static uint8 gu8_LED2_Delay_Flag = DELAY_NOT_COMPLETE;
static uint8 gu8_LED3_Delay_Flag = DELAY_NOT_COMPLETE;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
int main(void)
{
  /* Create instance of  DIO_Cfg_s and initialize it with zeros */
  DIO_Cfg_s str_DIO_Cfg_s = {0};

  /* Configure LED2 pin as digital output */
  str_DIO_Cfg_s.GPIO = GPIOB;
  str_DIO_Cfg_s.dir = OUTPUT;
  str_DIO_Cfg_s.pins = PIN6;

  /* Initialize LED2 pin */
  DIO_init(&str_DIO_Cfg_s);

  /* Configure LED3 pin as digital output */
  str_DIO_Cfg_s.GPIO = GPIOB;
  str_DIO_Cfg_s.dir = OUTPUT;
  str_DIO_Cfg_s.pins = PIN7;

  /* Initialize LED3 pin */
  DIO_init(&str_DIO_Cfg_s);

  /* Turn-off LED2 */
  DIO_Write(GPIOB, PIN6, LOW);
  /* Turn-off LED3 */
  DIO_Write(GPIOB, PIN7, LOW);

  /* Initialize TMU */
  gsi8_TMU_retval = TMU_Init();

  /* Enable interrupts */
  sei();

  /* Append LED2_DelayComplete */
  gsi8_TMU_retval = TMU_Start(LED2_DelayComplete, 100, PERIODIC);

  /* Append LED3_DelayComplete */
  gsi8_TMU_retval = TMU_Start(LED3_DelayComplete, 1000, PERIODIC);

  while(1)
  {
      /* TMU_Dispatcher call here */
      TMU_Dispatcher();

      /* These tasks are gonna be called from the */
      LED2_Toggle();
      LED3_Toggle();
      gsi8_TMU_retval = TMU_Stop(LED2_DelayComplete);

      /* Enter Idle sleep mode */
      CPU_Sleep(IDLE);
  }
  return 0;
}

/**
* @brief: LED2 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED2_Toggle(void)
{
  /* Toggle LED2 */
  if(gu8_LED2_Delay_Flag == DELAY_COMPLETE)
  {
      DIO_Toggle(GPIOB, PIN6);

      /* Reset flag */
      gu8_LED2_Delay_Flag = DELAY_NOT_COMPLETE;

      /* TMU delay request */
  }
  else
  {
    /* Do nothing */
  }
}

/**
* @brief: LED3 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED3_Toggle(void)
{
  /* Toggle LED3 */
  if(gu8_LED3_Delay_Flag == DELAY_COMPLETE)
  {
      DIO_Toggle(GPIOB, PIN7);

      /* Reset flag */
      gu8_LED3_Delay_Flag = DELAY_NOT_COMPLETE;

      /* TMU delay request */
  }
  else
  {
    /* Do nothing */
  }
}

/**
* @brief: LED2 Toggle Callback
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED2_DelayComplete(void)
{
  /* Indicate delay is complete */
  gu8_LED2_Delay_Flag = DELAY_COMPLETE;
}

/**
* @brief: LED3 Toggle Callback
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED3_DelayComplete(void)
{
  /* Indicate delay is complete */
  gu8_LED3_Delay_Flag = DELAY_COMPLETE;
}
