//*****************************************************************************
//
// File Name	: 'lcd_lib.c'
// Title		: 4-bit LCd interface
// Author		: Ahmed Osama
// Date			: Mar 5 2019
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#include "char_lcd.h"
#include "softwareDelay.h"

void LCD_EN_pulse(void){
	gpioPinWrite(LCD_EN_PORT, LCD_EN_PIN, HIGH);
	SwDelay_ms(1);
	gpioPinWrite(LCD_EN_PORT, LCD_EN_PIN, LOW);
	SwDelay_ms(1);
}

void LCD_config_pins(void){

	/* set LCD pins as outputs */
	gpioPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
	gpioPinDirection(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);
	gpioPinDirection(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);

	gpioPinDirection(LCD_D4_PORT, LCD_D4_PIN, OUTPUT);
	gpioPinDirection(LCD_D5_PORT, LCD_D5_PIN, OUTPUT);
	gpioPinDirection(LCD_D6_PORT, LCD_D6_PIN, OUTPUT);
	gpioPinDirection(LCD_D7_PORT, LCD_D7_PIN, OUTPUT);
}

void LCD_send_nibble(uint8 data){
	uint8 mask = 1;
	data >>= 4;
	if(data&mask)
		gpioPinWrite(LCD_D4_PORT, LCD_D4_PIN, HIGH);
	else
		gpioPinWrite(LCD_D4_PORT, LCD_D4_PIN, LOW);

	mask *= 2;
	if(data&mask)
		gpioPinWrite(LCD_D5_PORT, LCD_D5_PIN, HIGH);
	else
		gpioPinWrite(LCD_D5_PORT, LCD_D5_PIN, LOW);

	mask *= 2;
	if(data&mask)
		gpioPinWrite(LCD_D6_PORT, LCD_D6_PIN, HIGH);
	else
		gpioPinWrite(LCD_D6_PORT, LCD_D6_PIN, LOW);

	mask *= 2;
	if(data&mask)
		gpioPinWrite(LCD_D7_PORT, LCD_D7_PIN, HIGH);
	else
		gpioPinWrite(LCD_D7_PORT, LCD_D7_PIN, LOW);
}

void LCD_send_char(uint8 data)		//Sends Char to LCD
{
	gpioPinWrite(LCD_RS_PORT, LCD_RS_PIN, HIGH);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
	SwDelay_ms(1);
}
void LCD_send_command(uint8 data)	//Sends Command to LCD
{
	gpioPinWrite(LCD_RS_PORT, LCD_RS_PIN, LOW);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
	SwDelay_ms(1);
}
void LCD_init(void)//Initializes LCD
{
	LCD_config_pins();

	SwDelay_ms(20);
//	LCD_send_nibble(0x00);
//
//	gpioPinWrite(LCD_RS_PORT, LCD_RS_PIN, LOW);
//	gpioPinWrite(LCD_RW_PORT, LCD_RW_PIN, LOW);
//	gpioPinWrite(LCD_EN_PORT, LCD_EN_PIN, LOW);

	LCD_send_command(0x33);
	LCD_send_command(0x32);
	LCD_send_command(Four_bit); // 4-bit
	LCD_send_command(Cursor_on);
	LCD_send_command(Lcd_clear);
	SwDelay_ms(10);
	LCD_send_command(Increment_cursor);
	LCD_send_command(Cursor_off); // Cursor off
}
void LCD_clear(void)				//Clears LCD
{
	LCD_send_command(Lcd_clear);
}

void LCD_send_string(uint8* data)	//Outputs string to LCD
{
	while(*data){
		LCD_send_char(*data++);
	}
}

void LCD_goto_xy(uint8 x, uint8 y)	//Cursor to X Y position
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
