/*
 * tmu.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "tmu_lcfg.h"
#include "tmu.h"
#include "timer.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types ----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint8 u8_Tmu_InitStatus = NOT_INITIALIZED;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/
extern StrTmuConfig_t str_TmuConfig_s;

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/**
* @brief: Timer callback function
* @param: void
* Input : void
* Output: None
* @return: void
*/
static void Tmu_Timer_CBK(void);

/*- APIs IMPLEMENTATION -----------------------------------*/
/**
* @brief: TMU Initialization
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_Init(void)
{
  /* Create instance of Timer configuration structure and initialize it with zeros*/
  Timer_cfg_s str_Timer_Cfg_s = {0};

  /* Initialize corresponding timer */
  if(str_TmuConfig_s.timerCh == TMU_TIMER_CH0)
  {
      str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH0;
      str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64;
      #define TIM0
  }
  else if(str_TmuConfig_s.timerCh == TMU_TIMER_CH1)
  {
      str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH1;
      str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64; /* Needs to be changed */
      #define TIM1
  }
  else if(str_TmuConfig_s.timerCh == TMU_TIMER_CH2)
  {
      str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH2;
      str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64;
      #define TIM2
  }
  else
  {
      return E_NOK;
  }
  str_Timer_Cfg_s.Timer_Mode = TIMER_MODE;
  str_Timer_Cfg_s.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
  str_Timer_Cfg_s.CBK_Ptr = Tmu_Timer_CBK;
  Timer_Init(&str_Timer_Cfg_s);
  u8_Tmu_InitStatus = INITIALIZED;
  return E_OK;
}

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_DeInit(void)
{
  return E_OK;
}

/**
* @brief: TMU Start
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_Start(void)
{
  return E_OK;
}

/**
* @brief: TMU Stop
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_Stop(void)
{
  return E_OK;
}

/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_Dispatch(void)
{
  return E_OK;
}

/**
* @brief: Timer callback function
* @param: void
* Input : void
* Output: None
* @return: void
*/
static void Tmu_Timer_CBK(void)
{
  /* Start and pre-load timer with 6 counts to get exactly 1 mS at every overflow*/
#if defined (TIM0)
  Timer_Start(TIMER_CH0, 6);
#elif defined (TIM1)
  Timer_Start(TIMER_CH1, 6); /* Needs to be changed */
#elif defined (TIM2)
  Timer_Start(TIMER_CH2, 6);
#endif
}

