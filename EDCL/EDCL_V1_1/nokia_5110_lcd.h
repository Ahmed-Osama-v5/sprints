/*
 * nokia_5110_lcd.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_NOKIA_5110_LCD_H_
#define INC_NOKIA_5110_LCD_H_

#define LCD_CE_DDR		DDRD
#define LCD_CE_PORT		PORTD
#define LCD_CE_PIN		2

#define LCD_DC_DDR		DDRD
#define LCD_DC_PORT		PORTD
#define LCD_DC_PIN		4

#define LCD_RES_DDR		DDRD
#define LCD_RES_PORT	PORTD
#define LCD_RES_PIN		3

#define video_inverse     0x0D
#define function_set_norm 0x20
#define function_set_ext  0x21
#define set_vop           0xBF // range ( 0x80 - 0xFF)
#define set_temp          0x07 // range ( 0x04 - 0x07)
#define LCD_bias_48       0x13 // range ( 0x10 - 0x17)
#define display_norm      0x0C

#define LCD_CONTRAST      0x40


void NokiaLCD_init(void);
void NokiaLCD_send_data(char data);
void NokiaLCD_send_command(char data);
void NokiaLCD_send_char(char character);
void NokiaLCD_send_string(char *character);
void NokiaLCD_goto_x_y(char x,char y);
void NokiaLCD_Clear(void);
//void PCD8544_Image();

#endif /* INC_NOKIA_5110_LCD_H_ */
