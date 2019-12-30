/*
 * main.c
 *
 *  Created on: Dec 22, 2019
 *      Author: Ahmed Osama
 */

#include "std_types.h"
#include "interrupt.h"
#include "dio.h"
#include "softwareDelay.h"
#include "uart.h"
#include "spi.h"
#include "timer.h"
#include "pushButton.h"
#include "char_lcd.h"

#define NO_TRANSMISSION				0
#define START_TRANSMISSION			1
#define TIME_TRANSMISSION			2
#define SPEED_TRANSMISSION			3

uint8 gu8_OVFs = 0;
uint8 gu8_Seconds = 0;
uint8 gu8_speed = 0;
uint8 gu8_SPI_Transmission_Flag = NO_TRANSMISSION;
uint8 gu8_Time_Speed_Transmission_Flag = TIME_TRANSMISSION;

static void timer0_CBK_Func(void)
{
	if(gu8_OVFs < 61)
	{
		gu8_OVFs++;
	}
	else
	{
		//DIO_Toggle(GPIOC, PIN0);
		gu8_Seconds++;
		gu8_OVFs = 0;
		if(gu8_SPI_Transmission_Flag == NO_TRANSMISSION)
		{
			gu8_SPI_Transmission_Flag = START_TRANSMISSION;
		}
	}

}

int main(void)
{
	/**
	 * Initialize UART
	 * Initialize SPI
	 * Initialize Timer
	 * Initialize pButtons
	 */

	/* Create instance of UART configuration structure */
	UART_cfg_s str_UART_s = {0};

	str_UART_s.u32_BaudRate = 9600;
	str_UART_s.u8_DataSize = UART_8_BIT;
	str_UART_s.u8_DesiredOperation = TRANSCEIVER;
	str_UART_s.u8_DoubleSpeed = UART_NO_DOUBLE_SPEED;
	str_UART_s.u8_ParityBit = UART_NO_PARITY;
	str_UART_s.u8_InterruptMode = UART_POLLING;
	str_UART_s.u8_StopBit = UART_ONE_STOP_BIT;
	str_UART_s.DataRegisterEmpty_Cbk_ptr = NULL;
	str_UART_s.Resceive_Cbk_ptr = NULL;
	str_UART_s.Transmit_Cbk_ptr = NULL;

	/* Initialize UART */
	UART_Init(&str_UART_s);

	LCD_init();

	/* Create instance of SPI configuration structure */
	SPI_Cfg_s str_SPI_s = {0};

	str_SPI_s.u8_SPIMode = MASTER;
	str_SPI_s.u8_DataMode = MODE_0;
	str_SPI_s.u8_DataOrder = MSB;
	str_SPI_s.u8_Prescaler = SPI_PRESCALER_32; /* 500 KHz */
	str_SPI_s.u8_InterruptMode = POLLING;
	str_SPI_s.CBK_Func = NULL;

	/* Initialize SPI */
	SPI_Init(&str_SPI_s);

	/* Create instance of Timer configuration structure */
	Timer_cfg_s str_Timer_s = {0};
	str_Timer_s.Timer_CH_NO = TIMER_CH0;
	str_Timer_s.Timer_Mode = TIMER_MODE;
	str_Timer_s.Timer_Prescaler = TIMER_PRESCALER_1024;
	str_Timer_s.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
	str_Timer_s.CBK_Ptr = timer0_CBK_Func;

	/* Initialize Timer0 */
	Timer_Init(&str_Timer_s);

	pushButton_Init(BTN_0);
	pushButton_Init(BTN_1);

	DIO_Cfg_s str_DIO_s = {0};

	/* Initialize Debug LED */
	/*
	str_DIO_s.GPIO = GPIOC;
	str_DIO_s.dir = OUTPUT;
	str_DIO_s.pins = PIN0;
	DIO_init(&str_DIO_s);
	*/

	/* Initialize SPI SS */
	str_DIO_s.GPIO = GPIOB;
	str_DIO_s.dir = OUTPUT;
	str_DIO_s.pins = PIN4;
	DIO_init(&str_DIO_s);

	/* Enable global interrupts */
	sei();

	uint8 u8_data = 1;

	/* Wait for user to hit "t" */
	while(1)
	{
		UART_ReceiveByte(&u8_data);
		if(u8_data == '\r')
		{
			break;
		}
		else
		{
			u8_data -= 48;
			gu8_Seconds *= 10;
			gu8_Seconds += u8_data;
		}
	}

	/* Wait for user to hit "s" */
	while(1)
	{
		UART_ReceiveByte(&u8_data);
		if(u8_data == '\r')
		{
			break;
		}
		else
		{

			u8_data -= 48;
			gu8_speed *= 10;
			gu8_speed += u8_data;
		}
	}

	Timer_Start(TIMER_CH0, 255);
	/* uint8 u8_spi_ISR_Flag = NOT_TRIGGERED; */
	DIO_Write(GPIOB, PIN4, HIGH);

	char lcd_buffer[5];
	while(1)
	{
		LCD_goto_xy(0, 0);
		sprintf(lcd_buffer, "%d  ", gu8_Seconds);
		LCD_send_string(lcd_buffer);
		pushButton_Update();
		if(pushButton_GetStatus(BTN_0) == Pressed)
		{
			cli();
			gu8_speed++;
			sei();
		}
		else
		{

		}

		if(pushButton_GetStatus(BTN_1) == Pressed)
		{
			cli();
			gu8_speed--;
			sei();
		}
		else
		{

		}

		if(gu8_SPI_Transmission_Flag == START_TRANSMISSION)
		{
			DIO_Write(GPIOB, PIN4, LOW);
			if(gu8_Time_Speed_Transmission_Flag == TIME_TRANSMISSION)
			{
				SPI_SendByte(gu8_Seconds);
//				/* Poll SPI ISR Flag */
//				while(u8_spi_ISR_Flag == NOT_TRIGGERED)
//				{
//					SPI_GetStatus(&u8_spi_ISR_Flag);
//				}
				SPI_ClearFlag();
				SwDelay_ms(1);

				gu8_Time_Speed_Transmission_Flag = SPEED_TRANSMISSION;
			}
			else
			{
				SPI_SendByte(gu8_speed);
//				/* Poll SPI ISR Flag */
//				while(u8_spi_ISR_Flag == NOT_TRIGGERED)
//				{
//					SPI_GetStatus(&u8_spi_ISR_Flag);
//				}
				SPI_ClearFlag();
				SwDelay_ms(1);
				gu8_Time_Speed_Transmission_Flag = TIME_TRANSMISSION;
				gu8_SPI_Transmission_Flag = NO_TRANSMISSION;
			}
			DIO_Write(GPIOB, PIN4, HIGH);
		}
	}
	return 0;
}

