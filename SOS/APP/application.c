/*
 * File       : application.c
 * Project    : Small OS (SOS)
 * Target     : ATmega32
 * Created on : Jan 12, 2020
 * Author     : Ahmed Osama
 * Version    : 1.0
 */
/*- INCLUDES ----------------------------------------------*/
#include "std_types.h"
#include "interrupt.h"
#include "sleep.h"
#include "dio.h"
#include "SOS.h"

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
* @brief: LED1 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED1_Toggle(void);

/**
* @brief: LED2 Toggle
* @param: void
* Input : void
* Output: None
* @return: void
*/
void LED2_Toggle(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static sint8 gsi8_SOS_retval;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

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

  /* Turn-off LED0 */
  DIO_Write(GPIOB, PIN4, LOW);

  /* Turn-off LED1 */
  DIO_Write(GPIOB, PIN5, LOW);

  /* Turn-off LED2 */
  DIO_Write(GPIOB, PIN6, LOW);

  /* Initialize SOS */
  gsi8_SOS_retval = SOS_Init();

  /* Enable interrupts */
  sei();

  /* Create instance of SOS_TCB */
  strSOS_TCB_t strSOS_TaskCB = {0};

  /* Configure LED0_Toggle task */

  strSOS_TaskCB.ptrSOS_Task = LED0_Toggle;
  strSOS_TaskCB.u8_SOSTask_Priority = 0;
  strSOS_TaskCB.u16_SOSTask_Periodicity = 200;
  strSOS_TaskCB.u8_SOSTask_State = READY_STATE;
  strSOS_TaskCB.u16_SystemTick_Counter = 0;

  /* Append LED0_Toggle */
  gsi8_SOS_retval = SOS_CreateTask(&strSOS_TaskCB);

  /* Configure LED1_Toggle task */
  strSOS_TaskCB.ptrSOS_Task = LED1_Toggle;
  strSOS_TaskCB.u8_SOSTask_Priority = 1;
  strSOS_TaskCB.u16_SOSTask_Periodicity = 300;
  strSOS_TaskCB.u8_SOSTask_State = READY_STATE;
  strSOS_TaskCB.u16_SystemTick_Counter = 0;

  /* Append LED1_Toggle */
  gsi8_SOS_retval = SOS_CreateTask(&strSOS_TaskCB);

  /* Configure LED2_Toggle task */
  strSOS_TaskCB.ptrSOS_Task = LED2_Toggle;
  strSOS_TaskCB.u8_SOSTask_Priority = 2;
  strSOS_TaskCB.u16_SOSTask_Periodicity = 400;
  strSOS_TaskCB.u8_SOSTask_State = READY_STATE;
  strSOS_TaskCB.u16_SystemTick_Counter = 0;

  /* Append LED2_Toggle */
  gsi8_SOS_retval = SOS_CreateTask(&strSOS_TaskCB);

  while(1)
  {
      /* TMU_Dispatcher call here */
      SOS_Run();

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
  DIO_Toggle(GPIOB, PIN4);
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
  DIO_Toggle(GPIOB, PIN5);
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
  DIO_Toggle(GPIOB, PIN6);
}
