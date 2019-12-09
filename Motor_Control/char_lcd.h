//*****************************************************************************
//
// File Name	: 'lcd_lib.h'
// Title		: 4-bit LCd interface
// Author		: Ahmed Osama
// Date			: Mar 5 2019
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#ifndef CHAR_LCD_H_
#define CHAR_LCD_H_

#include "std_types.h"
#include "registers.h"
#include "gpio.h"

#define LCD_RS_PIN	BIT1 	//define MCU pin connected to LCD RS
#define LCD_RS_PORT	GPIOA

#define LCD_RW_PIN	BIT2 	//define MCU pin connected to LCD R/W
#define LCD_RW_PORT	GPIOA

#define LCD_EN_PIN	BIT3	//define MCU pin connected to LCD E
#define LCD_EN_PORT	GPIOA

#define LCD_D4_PIN	BIT4	//define MCU pin connected to LCD D4
#define LCD_D4_PORT	GPIOA

#define LCD_D5_PIN	BIT5	//define MCU pin connected to LCD D5
#define LCD_D5_PORT	GPIOA

#define LCD_D6_PIN	BIT6	//define MCU pin connected to LCD D6
#define LCD_D6_PORT	GPIOA

#define LCD_D7_PIN	BIT7	//define MCU pin connected to LCD D7
#define LCD_D7_PORT	GPIOA

/* LCD Commands definition */
#define Lcd_clear           0x01
#define Return_home         0x02
#define Decrement_cursor    0x04
#define Shift_display_right 0x05
#define Increment_cursor    0x06
#define Shift_display_left  0x07
#define Shift_cursor_left   0x10
#define Shift_cursor_right  0x14
#define Four_bit            0x28
#define Eight_bit           0x38
#define Cursor_off          0x0C
#define Cursor_on           0x0E

// cursor position to DDRAM mapping
#define LCD_DDRAM           7	//DB7: set DD RAM address
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54


void LCD_EN_pulse(void);
void LCD_config_pins(void); // configure LCD pins.
void LCD_send_nibble(uint8 data); // re-maps data bits to LCD Pins.
void LCD_send_char(char data);		//forms data ready to send to LCD
void LCD_send_command(uint8 data);	//forms command ready to send to LCD
void LCD_init(void);			//Initializes LCD
void LCD_clear(void);				//Clears LCD
void LCD_send_string(char* data);	//Outputs string to LCD
void LCD_goto_xy(uint8 x, uint8 y);	//Cursor to X Y position


#endif // LCD_H_

