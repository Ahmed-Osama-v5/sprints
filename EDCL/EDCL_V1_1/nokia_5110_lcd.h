/*
 * nokia_5110_lcd.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_NOKIA_5110_LCD_H_
#define INC_NOKIA_5110_LCD_H_

#define video_inverse     0x0D
#define function_set_norm 0x20
#define function_set_ext  0x21
#define set_vop           0xBF // range ( 0x80 - 0xFF)
#define set_temp          0x07 // range ( 0x04 - 0x07)
#define LCD_bias_48       0x13 // range ( 0x10 - 0x17)
#define display_norm      0x0C

#define LCD_CONTRAST      0x40


void PCD8544_init(void);
void PCD8544_send_data(char data);
void PCD8544_send_command(char data);
void PCD8544_send_char(char character);
void PCD8544_send_string(char *character);
void set_x_y(char x,char y);
void PCD8544_RAM_Clear(void);
//void PCD8544_Image();

#endif /* INC_NOKIA_5110_LCD_H_ */
