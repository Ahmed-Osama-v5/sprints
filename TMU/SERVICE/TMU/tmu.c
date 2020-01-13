/*
 * tmu.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "tmu_lcfg.h"
#include "tmu.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types ----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint8 gsu8_TMUInitStatus = NOT_INITIALIZED;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/
extern gstrTMUConfig_t gstr_TMUConfig_s;

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/**
* @brief: Timer callback function
* @param: void
* Input : void
* Output: None
* @return: void
*/
void TMU_TimerOvf_CBK(void);

/*- APIs IMPLEMENTATION -----------------------------------*/
/**
* @brief: TMU Initialization
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Init(void)
{
  sint8 retVal = TMU_BASE_ERROR + SUCCESS;

  /* Create instance of Timer configuration structure and initialize it with zeros*/
  Timer_cfg_s str_Timer_Cfg_s = {0};

  /* Initialize corresponding timer */
  if(gstr_TMUConfig_s.timerCh == TIMER_CH0)
  {
      str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH0;
      str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64;
  }
  else if(gstr_TMUConfig_s.timerCh == TIMER_CH1)
  {
      str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH1;
      str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64; /* Needs to be changed */
  }
  else if(gstr_TMUConfig_s.timerCh == TIMER_CH2)
  {
      str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH2;
      str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64;
  }
  else
  {
      retVal = TMU_BASE_ERROR + ERROR_NULL_POINTER;
  }
  str_Timer_Cfg_s.Timer_Mode = TIMER_MODE;
  str_Timer_Cfg_s.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
  str_Timer_Cfg_s.CBK_Ptr = TMU_TimerOvf_CBK;
  Timer_Init(&str_Timer_Cfg_s);
  gsu8_TMUInitStatus = INITIALIZED;

  return retVal;
}

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_DeInit(void)
{
    /* Remember to make a Timer_DeInit function */
    sint8 retVal = TMU_BASE_ERROR + SUCCESS;
    gsu8_TMUInitStatus = NOT_INITIALIZED;
    return retVal;
}

/**
* @brief: TMU Start
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Start(void)
{
    sint8 retVal = TMU_BASE_ERROR + SUCCESS;
    if(gsu8_TMUInitStatus == NOT_INITIALIZED)
    {
        retVal = TMU_BASE_ERROR + ERROR_NOT_INITIALIZED;
    }
    else
    {
	/* Start and pre-load timer with 6 counts to get exactly 1 mS at every overflow */
	#if defined TMU_TIMER_CH0
	  Timer_Start(TIMER_CH0, 6);
	#elif defined TMU_TIMER_CH1
	  Timer_Start(TIMER_CH1, 6); /* Needs to be changed */
	#elif defined TMU_TIMER_CH2
	  Timer_Start(TIMER_CH2, 6);
	#endif
    }
    return retVal;
}

/**
* @brief: TMU Stop
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Stop(void)
{
    sint8 retVal = TMU_BASE_ERROR + SUCCESS;
    if(gsu8_TMUInitStatus == NOT_INITIALIZED)
    {
	retVal = TMU_BASE_ERROR + ERROR_NOT_INITIALIZED;
    }
    else
    {
    /* Stop timer */
    #if defined TMU_TIMER_CH0
      Timer_Stop(TIMER_CH0);
    #elif defined TMU_TIMER_CH1
      Timer_Stop(TIMER_CH1); /* Needs to be changed */
    #elif defined TMU_TIMER_CH2
      Timer_Stop(TIMER_CH2);
    #endif
    }
    return retVal;
}

/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Dispatch(void)
{
    sint8 retVal = TMU_BASE_ERROR + SUCCESS;
    return retVal;
}

/**
* @brief: Timer callback function
* @param: void
* Input : void
* Output: None
* @return: void
*/
void TMU_TimerOvf_CBK(void)
{
  /* Start and pre-load timer with 6 counts to get exactly 1 mS at every overflow */
#if defined TMU_TIMER_CH0
  Timer_Start(TIMER_CH0, 6);
#elif defined TMU_TIMER_CH1
  Timer_Start(TIMER_CH1, 6); /* Needs to be changed */
#elif defined TMU_TIMER_CH2
  Timer_Start(TIMER_CH2, 6);
#endif
}

