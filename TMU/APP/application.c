/*
 * application.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */
/*- INCLUDES ----------------------------------------------*/
#include "std_types.h"
#include "tmu.h"
#include "BCM.h"
#include "interrupt.h"
#include "sleep.h"
#include "dio.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/**
* @brief: LED0 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED0_Toggle(void);

/**
* @brief: LED0 Delay Callback
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED0_DelayComplete(void);

/**
* @brief: LED1 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED1_Toggle(void);

/**
* @brief: LED1 Delay Callback
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED1_DelayComplete(void);

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

void TransmitComplete(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static sint8 gsi8_TMU_retval;
static uint8 gu8_LED0_Delay_Flag = DELAY_NOT_COMPLETE;
static uint8 gu8_LED1_Delay_Flag = DELAY_NOT_COMPLETE;
static uint8 gu8_LED2_Delay_Flag = DELAY_NOT_COMPLETE;
static uint8 gu8_LED3_Delay_Flag = DELAY_NOT_COMPLETE;

static sint8 gi8_BCM_retval;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/
uint8 buffer[10];
ptrBuffer ptrTx_Buffer = NULL;

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
void TransmitComplete(void)
{

}
/*- APIs IMPLEMENTATION -----------------------------------*/
int main(void)
{
  /* Create instance of  DIO_Cfg_s and initialize it with zeros */
  DIO_Cfg_s str_DIO_Cfg_s = {0};

  /* Configure LED0 pin as digital output */
  str_DIO_Cfg_s.GPIO = GPIOB;
  str_DIO_Cfg_s.dir = OUTPUT;
  str_DIO_Cfg_s.pins = PIN4;

  /* Initialize LED0 pin */
  DIO_init(&str_DIO_Cfg_s);

  /* Configure LED1 pin as digital output */
  str_DIO_Cfg_s.GPIO = GPIOB;
  str_DIO_Cfg_s.dir = OUTPUT;
  str_DIO_Cfg_s.pins = PIN5;

  /* Initialize LED1 pin */
  DIO_init(&str_DIO_Cfg_s);

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

  buffer[0] = 'A';
  buffer[1] = 'h';
  buffer[2] = 'm';
  buffer[3] = 'e';
  buffer[4] = 'd';

  ptrTx_Buffer = buffer;
  gptr_BCM_TransmitComplete_User_CBK_t ptrTxComplete_CBK = TransmitComplete;

  /* Initialize BCM */
  gi8_BCM_retval = BCM_Init(ptrTxComplete_CBK);

  /* Enable interrupts */
  sei();

  gi8_BCM_retval = BCM_Send(ptrTx_Buffer, 5);

  /* Append LED0_DelayComplete */
  gsi8_TMU_retval = TMU_Start(LED0_DelayComplete, 100, PERIODIC);

  /* Append LED1_DelayComplete */
  gsi8_TMU_retval = TMU_Start(LED1_DelayComplete, 800, ONE_SHOT);

  /* Append LED2_DelayComplete */
  gsi8_TMU_retval = TMU_Start(LED2_DelayComplete, 400, PERIODIC);

  /* Append LED3_DelayComplete */
  gsi8_TMU_retval = TMU_Start(LED3_DelayComplete, 200, ONE_SHOT);

  while(1)
  {
      /* TMU_Dispatcher call here */
      TMU_Dispatcher();

      /* These tasks are gonna be called from the */
      LED0_Toggle();
      LED1_Toggle();
      LED2_Toggle();
      LED3_Toggle();
      /* gsi8_TMU_retval = TMU_Stop(LED2_DelayComplete); */

      /* Enter Idle sleep mode */
      CPU_Sleep(IDLE);
  }
  return 0;
}

/**
* @brief: LED0 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED0_Toggle(void)
{
  /* Toggle LED0 */
  if(gu8_LED0_Delay_Flag == DELAY_COMPLETE)
  {
      DIO_Toggle(GPIOB, PIN4);

      /* Reset flag */
      gu8_LED0_Delay_Flag = DELAY_NOT_COMPLETE;
  }
  else
  {
    /* Do nothing */
  }
}

/**
* @brief: LED1 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED1_Toggle(void)
{
  /* Toggle LED1 */
  if(gu8_LED1_Delay_Flag == DELAY_COMPLETE)
  {
      DIO_Toggle(GPIOB, PIN5);

      /* Reset flag */
      gu8_LED1_Delay_Flag = DELAY_NOT_COMPLETE;
  }
  else
  {
    /* Do nothing */
  }
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
  }
  else
  {
    /* Do nothing */
  }
}

/**
* @brief: LED0 Delay Callback
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED0_DelayComplete(void)
{
  /* Indicate delay is complete */
  gu8_LED0_Delay_Flag = DELAY_COMPLETE;
}

/**
* @brief: LED1 Delay Callback
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED1_DelayComplete(void)
{
  /* Indicate delay is complete */
  gu8_LED1_Delay_Flag = DELAY_COMPLETE;
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
