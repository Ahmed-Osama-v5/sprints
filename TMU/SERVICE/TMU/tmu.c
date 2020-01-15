/*
 * tmu.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "tmu.h"

/*- LOCAL MACROS ------------------------------------------*/
#define OVF_NOT_TRIGGERED	(0)
#define OVF_TRIGGERED		(1)

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/**
* @brief: Timer callback function
* @param: void
* Input : void
* Output: None
* @return: void
*/
static void TMU_TimerOvf_CBK(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
/* Indicates TMU is initialized or not */
static uint8 gsu8_TMUInitStatus = NOT_INITIALIZED;

/* Indicates timer overflow has occurred or not */
static volatile uint8 gu8_TMU_TimerOvf_Flag = OVF_NOT_TRIGGERED;

/* OverFlow counter */
static volatile uint8 gu8_OvfCounter = 0;

/* Array elements count */
static uint8 gu8_ArrayElementCount = 0;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

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
  sint8 i8_retVal = TMU_BASE_ERROR + SUCCESS;

  /* Initialize TMU_TCB array with zeros */
  uint8 u8_i;
  for(u8_i=0;u8_i<MAX_TASK_COUNT;u8_i++)
  {
      gstrTMU_TCB_s[u8_i].ptrTMU_DelayComplete_UserFunc_CBK = NULL;
      gstrTMU_TCB_s[u8_i].u16_Delay = 0;
      gstrTMU_TCB_s[u8_i].u16_MilliSecond_Count = 0;
      gstrTMU_TCB_s[u8_i].u8_Periodicity = 0;
  }

  /* Create instance of Timer configuration structure and initialize it with zeros*/
  Timer_cfg_s str_Timer_Cfg_s = {0};

  /* Configure corresponding timer */
  #if defined TMU_TIMER_CH0
    str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH0;
    str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64;
  #elif defined TMU_TIMER_CH1
    str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH1;
    str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64; /* Needs to be changed */
  #elif defined TMU_TIMER_CH2
    str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH2;
    str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64;
  #endif
  str_Timer_Cfg_s.Timer_Mode = TIMER_MODE;
  str_Timer_Cfg_s.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
  str_Timer_Cfg_s.CBK_Ptr = TMU_TimerOvf_CBK;

  /* Initialize timer */
  Timer_Init(&str_Timer_Cfg_s);

  /* Indicate TMU is initialized */
  gsu8_TMUInitStatus = INITIALIZED;

  return i8_retVal;
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
    sint8 i8_retVal = TMU_BASE_ERROR + SUCCESS;

    /* Fill TMU_TCB array with zeros */
    uint8 u8_i;
    for(u8_i=0;u8_i<MAX_TASK_COUNT;u8_i++)
    {
	gstrTMU_TCB_s[u8_i].ptrTMU_DelayComplete_UserFunc_CBK = NULL;
	gstrTMU_TCB_s[u8_i].u16_Delay = 0;
	gstrTMU_TCB_s[u8_i].u16_MilliSecond_Count = 0;
	gstrTMU_TCB_s[u8_i].u8_Periodicity = 0;
    }

    /* TODO: */
    /* DeInit used timer */
    #if defined TMU_TIMER_CH0
      /* DeInit Timer0 */
    #elif defined TMU_TIMER_CH1
      /* DeInit Timer1 */
    #elif defined TMU_TIMER_CH2
      /* DeInit Timer2 */
    #endif

    /* Indicate TMU is not initialized */
    gsu8_TMUInitStatus = NOT_INITIALIZED;
    return i8_retVal;
}

/**
* @brief: Appends Task block elements to the TCB array
* @param: ptrFun_User_CBK: pointer to callback function,
* 	  u16_Delay: requested delay,
* 	  u8_Periodicity: periodic or one shot
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Start(gptrTMU_DelayCompleteFun_User_CBK ptrFun_User_CBK, u16_Delay_t u16_Delay, uint8 u8_Periodicity)
{
    sint8 i8_retVal = TMU_BASE_ERROR + SUCCESS;
    if(gsu8_TMUInitStatus == NOT_INITIALIZED)
    {
	i8_retVal = TMU_BASE_ERROR + ERROR_NOT_INITIALIZED;
    }
    else
    {
	if(NULL == ptrFun_User_CBK)
	{
	    /* Error NULL pointer */
	    i8_retVal = TMU_BASE_ERROR + ERROR_NULL_POINTER;
	}
	else
	{
	    /* Assign TCB struct members */
	    gstrTMU_TCB_s[gu8_ArrayElementCount].ptrTMU_DelayComplete_UserFunc_CBK = ptrFun_User_CBK;
	    gstrTMU_TCB_s[gu8_ArrayElementCount].u16_Delay = u16_Delay;
	    gstrTMU_TCB_s[gu8_ArrayElementCount].u16_MilliSecond_Count = 0;
	    gstrTMU_TCB_s[gu8_ArrayElementCount].u8_Periodicity = u8_Periodicity;

	    /* Check if this is the first element in the array to start the timer */
	    if(gu8_ArrayElementCount == 0)
	    {
	      /* Start and pre-load timer with 6 counts to get exactly 1 mS at every overflow */
	      #if defined TMU_TIMER_CH0
		Timer_Start(TIMER_CH0, 6);
	      #elif defined TMU_TIMER_CH1
		Timer_Start(TIMER_CH1, 65286);
	      #elif defined TMU_TIMER_CH2
		Timer_Start(TIMER_CH2, 6);
	      #endif
	    }

	    /* Increment Array index */
	    gu8_ArrayElementCount++;
	}
    }
    return i8_retVal;
}

/**
* @brief: TMU Stop
* @param: ptrFun_User_CBK: pointer to callback function
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Stop(gptrTMU_DelayCompleteFun_User_CBK ptrFun_User_CBK)
{
    sint8 i8_retVal = TMU_BASE_ERROR + SUCCESS;

    if(gsu8_TMUInitStatus == NOT_INITIALIZED)
    {
	i8_retVal = TMU_BASE_ERROR + ERROR_NOT_INITIALIZED;
    }
    else
    {
      uint8 u8_i;

      /* Check if TCB struct array is empty */
      if(gu8_ArrayElementCount == 0)
      {
	  /* Error struct array is empty */
	  i8_retVal = TMU_BASE_ERROR + ERROR_ARRAY_EMPTY;
      }
      else
      {
	  /* Loop through TCB struct array to find task to be removed */
	  for(u8_i=0;u8_i<MAX_TASK_COUNT;u8_i++)
	  {
	      if(gstrTMU_TCB_s[u8_i].ptrTMU_DelayComplete_UserFunc_CBK == ptrFun_User_CBK)
	      {
		  /* Handle special cases */
		  /* Check if one element only is present in the array or if the array is full */
		  if((gu8_ArrayElementCount == 1) || (gu8_ArrayElementCount == MAX_TASK_COUNT))
		  {
		      /* Restore default values */
		      gstrTMU_TCB_s[gu8_ArrayElementCount-1].ptrTMU_DelayComplete_UserFunc_CBK = NULL;
		      gstrTMU_TCB_s[gu8_ArrayElementCount-1].u16_Delay = 0;
		      gstrTMU_TCB_s[gu8_ArrayElementCount-1].u16_MilliSecond_Count = 0;
		      gstrTMU_TCB_s[gu8_ArrayElementCount-1].u8_Periodicity = 0;

		      /* Decrement array index */
		      gu8_ArrayElementCount--;
		  }
		  /* General case */
		  else
		  {
		      /* Store last element in the element to be removed */
		      gstrTMU_TCB_s[u8_i].ptrTMU_DelayComplete_UserFunc_CBK =  gstrTMU_TCB_s[gu8_ArrayElementCount-1].ptrTMU_DelayComplete_UserFunc_CBK;
		      gstrTMU_TCB_s[u8_i].u16_Delay = gstrTMU_TCB_s[gu8_ArrayElementCount-1].u16_Delay;
		      gstrTMU_TCB_s[u8_i].u16_MilliSecond_Count = gstrTMU_TCB_s[gu8_ArrayElementCount-1].u16_MilliSecond_Count;
		      gstrTMU_TCB_s[u8_i].u8_Periodicity = gstrTMU_TCB_s[gu8_ArrayElementCount-1].u8_Periodicity;

		      /* Restore default values for last element */
		      gstrTMU_TCB_s[gu8_ArrayElementCount-1].ptrTMU_DelayComplete_UserFunc_CBK = NULL;
		      gstrTMU_TCB_s[gu8_ArrayElementCount-1].u16_Delay = 0;
		      gstrTMU_TCB_s[gu8_ArrayElementCount-1].u16_MilliSecond_Count = 0;
		      gstrTMU_TCB_s[gu8_ArrayElementCount-1].u8_Periodicity = 0;

		      /* Decrement array index */
		      gu8_ArrayElementCount--;
		  }
	      }
	  }
      }

      /* Check if array is empty to stop the timer */
      if(gu8_ArrayElementCount == 0)
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
    }
    return i8_retVal;
}

/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Dispatcher(void)
{
    sint8 i8_retVal = TMU_BASE_ERROR + SUCCESS;
    if(gu8_TMU_TimerOvf_Flag == OVF_TRIGGERED)
    {
	uint8 u8_i;
	/* Loop through Tasks in the array and increment counters */
	for(u8_i=0;u8_i<gu8_ArrayElementCount;u8_i++)
	{
	    if(NULL == gstrTMU_TCB_s[u8_i].ptrTMU_DelayComplete_UserFunc_CBK)
	    {
		/* Do nothing */
	    }
	    else
	    {
		/* Increment milliSeconds counter */
		gstrTMU_TCB_s[u8_i].u16_MilliSecond_Count++;
	    }
	}

	/* Loop through TCB array and handle each one */
	for(u8_i=0;u8_i<gu8_ArrayElementCount;u8_i++)
	{
	    if(NULL == gstrTMU_TCB_s[u8_i].ptrTMU_DelayComplete_UserFunc_CBK)
	    {
		/* Error NULL pointer */
		i8_retVal = TMU_BASE_ERROR + ERROR_NULL_POINTER;

		/* Break the loop */
		break;
	    }
	    else
	    {
		/* Check if requested delay is reached */
		if(gstrTMU_TCB_s[u8_i].u16_MilliSecond_Count >= gstrTMU_TCB_s[u8_i].u16_Delay)
		{
		    /* Zero milliSecond counter */
		    gstrTMU_TCB_s[u8_i].u16_MilliSecond_Count = 0;

		    /* Execute corresponding callback function */
		    gstrTMU_TCB_s[u8_i].ptrTMU_DelayComplete_UserFunc_CBK();

		    /* Check if Task is one shot to remove it from TCB array */
		    if(gstrTMU_TCB_s[u8_i].u8_Periodicity == ONE_SHOT)
		    {
			/* Remove Task from TCB array */
			TMU_Stop(gstrTMU_TCB_s[u8_i].ptrTMU_DelayComplete_UserFunc_CBK);
		    }
		    else
		    {
			/* Do nothing */
		    }
		}
		else
		{
		    /* Do nothing */
		}
	    }
	}
    }
    else
    {
	/* Do nothing */
    }
    return i8_retVal;
}

/**
* @brief: Timer callback function
* @param: void
* Input : void
* Output: None
* @return: void
*/
static void TMU_TimerOvf_CBK(void)
{
  /* Increment overflow counter */
  gu8_OvfCounter++;
  if(gu8_OvfCounter == TMU_RESOLUTION)
  {
      /* Indicate timer overflow has occurred */
      gu8_TMU_TimerOvf_Flag = OVF_TRIGGERED;

      /* Reset overflow counter */
      gu8_OvfCounter = 0;
  }
  else
  {
      /* Do nothing */
  }
  /* Start and pre-load timer to get exactly 1 mS at every overflow */
#if defined TMU_TIMER_CH0
  Timer_Start(TIMER_CH0, 6);
#elif defined TMU_TIMER_CH1
  Timer_Start(TIMER_CH1, 65286);
#elif defined TMU_TIMER_CH2
  Timer_Start(TIMER_CH2, 6);
#endif
}

