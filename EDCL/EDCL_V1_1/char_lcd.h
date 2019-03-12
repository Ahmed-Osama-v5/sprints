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

#include <inttypes.h>

#define LCD_RS_PIN	0 	//define MCU pin connected to LCD RS
#define LCD_RS_DDR	DDRB
#define LCD_RS_PORT	PORTB

#define LCD_RW_PIN	1 	//define MCU pin connected to LCD R/W
#define LCD_RW_DDR	DDRB
#define LCD_RW_PORT	PORTB

#define LCD_EN_PIN	2	//define MCU pin connected to LCD E
#define LCD_EN_DDR	DDRB
#define LCD_EN_PORT	PORTB

#define LCD_D4_PIN	4	//define MCU pin connected to LCD D4
#define LCD_D4_DDR	DDRB
#define LCD_D4_PORT	PORTB

#define LCD_D5_PIN	5	//define MCU pin connected to LCD D5
#define LCD_D5_DDR	DDRB
#define LCD_D5_PORT	PORTB

#define LCD_D6_PIN	6	//define MCU pin connected to LCD D6
#define LCD_D6_DDR	DDRB
#define LCD_D6_PORT	PORTB

#define LCD_D7_PIN	7	//define MCU pin connected to LCD D7
#define LCD_D7_DDR	DDRB
#define LCD_D7_PORT	PORTB

// cursor position to DDRAM mapping
#define LCD_DDRAM           7	//DB7: set DD RAM address
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54


void LCD_EN_pulse(void);
void LCD_config_pins(void); // configure LCD pins.
void LCD_send_nibble(uint8_t data); // re-maps data bits to LCD Pins.
void LCD_send_char(uint8_t data);		//forms data ready to send to LCD
void LCD_send_command(uint8_t data);	//forms command ready to send to LCD
void LCD_init(void);			//Initializes LCD
void LCD_clear(void);				//Clears LCD
void LCD_send_string(uint8_t* data);	//Outputs string to LCD
void LCD_goto_xy(uint8_t x, uint8_t y);	//Cursor to X Y position


#endif // LCD_H_

