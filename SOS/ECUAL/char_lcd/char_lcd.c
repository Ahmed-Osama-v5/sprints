//*****************************************************************************
//
// File Name	: 'lcd_lib.c'
// Title		: 4-bit LCd interface
// Author		: Ahmed Osama
// Date			: Mar 5 2019
// Target MCU	: Atmel AVR series
// Modified		: Jan 24 2020
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#include "char_lcd.h"
#include "dio.h"

static void delay(void)
{
	/* 40 uS delay loop */
	uint16 u16_i;
	for(u16_i=0;u16_i<640;u16_i++)
	{
		asm("nop");
	}
}

void LCD_EN_pulse(void)
{
	DIO_Write(LCD_EN_GPIO, LCD_EN_PIN, HIGH);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	DIO_Write(LCD_EN_GPIO, LCD_EN_PIN, LOW);
}

void LCD_config_pins(void)
{
	/* set LCD pins as outputs */
	DIO_Cfg_s ST_dio = {0};
	ST_dio.GPIO = LCD_RS_GPIO;
	ST_dio.dir = OUTPUT;
	ST_dio.pins = LCD_RS_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_RW_GPIO;
	ST_dio.pins = LCD_RW_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_EN_GPIO;
	ST_dio.pins = LCD_EN_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D4_GPIO;
	ST_dio.pins = LCD_D4_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D5_GPIO;
	ST_dio.pins = LCD_D5_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D6_GPIO;
	ST_dio.pins = LCD_D6_PIN;
	DIO_init(&ST_dio);

	ST_dio.GPIO = LCD_D7_GPIO;
	ST_dio.pins = LCD_D7_PIN;
	DIO_init(&ST_dio);
}

void LCD_send_nibble(uint8 data)
{
	uint8 mask = 1;
	data >>= 4;
	if(data&mask)
		DIO_Write(LCD_D4_GPIO, LCD_D4_PIN, HIGH);
	else
		DIO_Write(LCD_D4_GPIO, LCD_D4_PIN, LOW);

	mask *= 2;
	if(data&mask)
		DIO_Write(LCD_D5_GPIO, LCD_D5_PIN, HIGH);
	else
		DIO_Write(LCD_D5_GPIO, LCD_D5_PIN, LOW);

	mask *= 2;
	if(data&mask)
		DIO_Write(LCD_D6_GPIO, LCD_D6_PIN, HIGH);
	else
		DIO_Write(LCD_D6_GPIO, LCD_D6_PIN, LOW);

	mask *= 2;
	if(data&mask)
		DIO_Write(LCD_D7_GPIO, LCD_D7_PIN, HIGH);
	else
		DIO_Write(LCD_D7_GPIO, LCD_D7_PIN, LOW);
}

void LCD_send_char(char data)
{
	DIO_Write(LCD_RS_GPIO, LCD_RS_PIN, HIGH);

	LCD_send_nibble(data);
	LCD_EN_pulse();
	delay();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
	delay();
}
void LCD_send_command(uint8 data)
{
	DIO_Write(LCD_RS_GPIO, LCD_RS_PIN, LOW);

	/* Higher nibble first */
	LCD_send_nibble(data);
	LCD_EN_pulse();
	delay();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
	delay();
}
void LCD_init(void)
{
	LCD_config_pins();

	DIO_Write(LCD_RS_GPIO, LCD_RS_PIN, LOW);
	DIO_Write(LCD_RW_GPIO, LCD_RW_PIN, LOW);
	DIO_Write(LCD_EN_GPIO, LCD_EN_PIN, LOW);

	LCD_send_command(0x32);
	LCD_send_command(Four_bit);
	LCD_send_command(Cursor_on);
	LCD_send_command(Lcd_clear);
	LCD_send_command(Increment_cursor);
	LCD_send_command(Cursor_off);
}
void LCD_clear(void)
{
	LCD_send_command(Lcd_clear);
}

void LCD_send_string(char* data)
{
	while(*data){
		LCD_send_char(*data++);
	}
}

void LCD_goto_xy(uint8 x, uint8 y)
{
	uint8 DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	// set data address
	LCD_send_command(1<<LCD_DDRAM | DDRAMAddr);

}
