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
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

void LCD_EN_pulse(void){
	LCD_EN_PORT |= (1 << LCD_EN_PIN);
	_delay_ms(1);
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
	_delay_ms(1);
}

void LCD_config_pins(void){

	/* set LCD pins as outputs */
	LCD_RS_DDR |= (1 << LCD_RS_PIN);
	LCD_RW_DDR |= (1 << LCD_RW_PIN);
	LCD_EN_DDR |= (1 << LCD_EN_PIN);

	LCD_D4_DDR |= (1 << LCD_D4_PIN);
	LCD_D5_DDR |= (1 << LCD_D5_PIN);
	LCD_D6_DDR |= (1 << LCD_D6_PIN);
	LCD_D7_DDR |= (1 << LCD_D7_PIN);
}

void LCD_send_nibble(uint8_t data){
	uint8_t mask = 1;
	data >>= 4;
	if(data&mask)
		LCD_D4_PORT |= (1 << LCD_D4_PIN);
	else
		LCD_D4_PORT &= ~(1 << LCD_D4_PIN);

	mask *= 2;
	if(data&mask)
		LCD_D5_PORT |= (1 << LCD_D5_PIN);
	else
		LCD_D5_PORT &= ~(1 << LCD_D5_PIN);

	mask *= 2;
	if(data&mask)
		LCD_D6_PORT |= (1 << LCD_D6_PIN);
	else
		LCD_D6_PORT &= ~(1 << LCD_D6_PIN);

	mask *= 2;
	if(data&mask)
		LCD_D7_PORT |= (1 << LCD_D7_PIN);
	else
		LCD_D7_PORT &= ~(1 << LCD_D7_PIN);
}

void LCD_send_char(uint8_t data)		//Sends Char to LCD
{
	LCD_RS_PORT |= (1 << LCD_RS_PIN);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
}
void LCD_send_command(uint8_t data)	//Sends Command to LCD
{
	LCD_RS_PORT &= ~(1 << LCD_RS_PIN);

	LCD_send_nibble(data); // Higher nibble first
	LCD_EN_pulse();

	LCD_send_nibble(data<<4);
	LCD_EN_pulse();
}
void LCD_init(void)//Initializes LCD
{
	LCD_config_pins();

	_delay_ms(15);
	LCD_send_nibble(0x00);

	LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
	LCD_RW_PORT &= ~(1 << LCD_RW_PIN);
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);

	LCD_send_command(0x33);
	LCD_send_command(0x32);
	LCD_send_command(0x28); // 4-bit
	LCD_send_command(0x0E);
	LCD_send_command(0x01);
	_delay_ms(2);
	LCD_send_command(0x06);
	LCD_send_command(0x0C); // Cursor off
}
void LCD_clear(void)				//Clears LCD
{
	LCD_send_command(0x01);
}

void LCD_send_string(uint8_t* data)	//Outputs string to LCD
{
	while(*data){
		LCD_send_char(*data++);
	}
}

void LCD_goto_xy(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	uint8_t DDRAMAddr;
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
