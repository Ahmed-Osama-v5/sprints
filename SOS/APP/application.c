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
#include "dio.h"
#include "SOS.h"
#include "char_lcd.h"
#include "keypad.h"
#include "sleep.h"

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
* @brief: Initialize system GPIOs and peripherals
* @param: void
* @return: void
*/
static void system_Init(void);

/**
* @brief: get pressed key from keypad
* @param: void
* @return: void
*/
static void getKey(void);

/**
* @brief: Set cursor to home location
* @param: void
* @return: void
*/
static void LCD_Home(void);

/**
* @brief: Sends data inside the buffer
* @param: void
* @return: void
*/
static void LCD_SendBuffer(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static sint8 gsi8_SOS_retval;
static uint8 gau8_LCD_Buffer[16];
static uint8 gu8_KeyPressed = NO_KEY_PRESSED;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/**
* @brief: get pressed key from keypad
* @param: void
* @return: void
*/
static void getKey(void)
{
	KeyPad_getPressedKey(&gu8_KeyPressed);
}

/**
* @brief: Set cursor to home location
* @param: void
* @return: void
*/
static void LCD_Home(void)
{
	LCD_goto_xy(0, 0);
}

/**
* @brief: Sends data inside the buffer
* @param: void
* @return: void
*/
static void LCD_SendBuffer(void)
{
	if(gu8_KeyPressed == NO_KEY_PRESSED)
	{
		/* Do nothing */
		LCD_send_char(' ');
	}
	else
	{
		/* Print key on LCD */
		LCD_send_char(gu8_KeyPressed+48);
		//LCD_send_char('P');
	}
}

/**
* @brief: LED0 Toggle
* @param: void
* @return: void
*/
void LED0_Toggle(void)
{
  /* Toggle LED0 */
  DIO_Toggle(GPIOB, PIN4);
}


/*- APIs IMPLEMENTATION -----------------------------------*/
int main(void)
{
	/* Initialize system GPIOs and peripherals */
	system_Init();

	/* Enable interrupts */
	sei();

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
* @brief: Initialize system GPIOs and peripherals
* @param: void
* @return: void
*/
static void system_Init(void)
{
	gau8_LCD_Buffer[0] = 'A';
	gau8_LCD_Buffer[1] = 'h';
	gau8_LCD_Buffer[2] = 'm';
	gau8_LCD_Buffer[3] = 'e';
	gau8_LCD_Buffer[4] = 'd';
	gau8_LCD_Buffer[5] = ' ';
	gau8_LCD_Buffer[6] = 'O';
	gau8_LCD_Buffer[7] = 's';
	gau8_LCD_Buffer[8] = 'a';
	gau8_LCD_Buffer[9] = 'm';
	gau8_LCD_Buffer[10] = 'a';

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

	/* Turn-off LED0 */
	DIO_Write(GPIOB, PIN4, LOW);

	/* Initialize SOS */
	gsi8_SOS_retval = SOS_Init();

	/* Create instance of SOS_TCB */
	strSOS_TCB_t strSOS_TaskCB = {0};

	/* Configure LED0_Toggle task */

	strSOS_TaskCB.ptrSOS_Task = LED0_Toggle;
	strSOS_TaskCB.u8_SOSTask_Priority = 10;
	strSOS_TaskCB.u16_SOSTask_Periodicity = 500;
	strSOS_TaskCB.u8_SOSTask_State = READY_STATE;
	strSOS_TaskCB.u16_SystemTick_Counter = 0;

	/* Append LED0_Toggle */
	gsi8_SOS_retval = SOS_CreateTask(&strSOS_TaskCB);

	/* Configure LCD_SendBuffer task */
	strSOS_TaskCB.ptrSOS_Task = LCD_SendBuffer;
	strSOS_TaskCB.u8_SOSTask_Priority = 6;
	strSOS_TaskCB.u16_SOSTask_Periodicity = 100;
	strSOS_TaskCB.u8_SOSTask_State = READY_STATE;
	strSOS_TaskCB.u16_SystemTick_Counter = 0;

	/* Append LCD_SendBuffer */
	gsi8_SOS_retval = SOS_CreateTask(&strSOS_TaskCB);

	/* Configure LCD_gotoRowCol task */
	strSOS_TaskCB.ptrSOS_Task = LCD_Home;
	strSOS_TaskCB.u8_SOSTask_Priority = 7;
	strSOS_TaskCB.u16_SOSTask_Periodicity = 100;
	strSOS_TaskCB.u8_SOSTask_State = READY_STATE;
	strSOS_TaskCB.u16_SystemTick_Counter = 0;

	/* Append LCD_gotoRowCol */
	gsi8_SOS_retval = SOS_CreateTask(&strSOS_TaskCB);

	/* Initialize keypad */
	KeyPad_init();
	gu8_KeyPressed = NO_KEY_PRESSED;

	/* Configure getKey task */
	strSOS_TaskCB.ptrSOS_Task = getKey;
	strSOS_TaskCB.u8_SOSTask_Priority = 0;
	strSOS_TaskCB.u16_SOSTask_Periodicity = 10;
	strSOS_TaskCB.u8_SOSTask_State = READY_STATE;
	strSOS_TaskCB.u16_SystemTick_Counter = 0;

	/* Append getKey */
	gsi8_SOS_retval = SOS_CreateTask(&strSOS_TaskCB);

	/* Initialize LCD */
	LCD_init();
}
