/*********************************
 * Project  : Electronic dc load V1.1.
 * Author   : Ahmed Osama.
 * MCU      : ATmega16A @ 16 MHz HSE.
 * Date     : Aug 9, 2018.
 * Modified : Mar 5, 2019.
 *********************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "spi.h"
#include "adc_mcp3202.h"
#include "nokia_5110_lcd.h"
#include "uart.h"
#include "i2c.h"
#include "rtc.h"
#include "ext_eep.h"
#include "pwm.h"
#include "config.h"

#define HOME_LAYOUT         1
#define LCD_SETUP_LAYOUT    2

#define FAN_CTRL        PINB0

void progressBar(uint8_t x, uint8_t y);
void homeLayout(void);
void lcdSetupLayout(void);

uint8_t cursor_index = 0;
uint8_t screenIndex = HOME_LAYOUT;
uint8_t contrast = LCD_CONTRAST;

uint16_t adcRead = 0;
double voltRead = 0;
char adcStr[5];

int main(void)
{
    var = 7;
    config_IO();
    UART_init(9600);
    MCP3202_Init();
    I2C_Master_Init();
    PWM0_init();
    UART_Send_String("EDCL V1.0\nBy/ Ahmed Osama\n");

    PCD8544_init();
    homeLayout();
    EEWriteByte(0, 0xAD);

    while(1)
    {
        adcRead = MCP3202_read(1);
        voltRead = ((adcRead * 5.0) / 4096) * 5.714;
        char str_number[6];
        str_number[0] = (voltRead / 10) + 48;
        str_number[1] = ((uint8_t)voltRead % 10) + 48;
        str_number[2] = '.';
        str_number[3] = ((uint8_t)(voltRead * 10) % 10) + 48;
        str_number[4] = ((uint8_t)(voltRead * 100) % 10) + 48;
        str_number[5] = 0;
        set_x_y(35,1);
        PCD8544_send_string(str_number);
        PCD8544_send_char('V');
        if(bit_is_clear(BUTTON_RIGHT_PINR, BUTTON_RIGHT_PIN))
        {
            UART_Send_String("Right\n");
            switch(screenIndex)
            {
            case LCD_SETUP_LAYOUT:
                if(contrast < 0x50)
                {
                    PCD8544_send_command(++contrast);
                }
                else
                {
                    contrast = LCD_CONTRAST;
                    PCD8544_send_command(contrast);
                }
                break;
            }
            _delay_ms(300);
        }
        if(bit_is_clear(BUTTON_DOWN_PINR, BUTTON_DOWN_PIN))
        {
            UART_Send_String("Down\n");
            if(cursor_index < 5)
            {
                set_x_y(0,cursor_index);
                PCD8544_send_char(' ');
                set_x_y(0,++cursor_index);
                PCD8544_send_char('>');
            }
            else
            {
                set_x_y(0,cursor_index);
                PCD8544_send_char(' ');
                cursor_index = 0;
                set_x_y(0,cursor_index);
                PCD8544_send_char('>');
            }
            _delay_ms(300);
        }
        if(bit_is_clear(BUTTON_OK_PINR, BUTTON_OK_PIN))
        {
            UART_Send_String("OK\n");
            switch(screenIndex)
            {
            case HOME_LAYOUT:
                switch(cursor_index)
                {
                case 5:
                    lcdSetupLayout();
                    cursor_index = 0;
                    break;
                default:
                    break;
                }
                break;
            case LCD_SETUP_LAYOUT:
                switch(cursor_index)
                {
                case 0:
                    PCD8544_send_command(video_inverse);
                    break;
                case 1:
                    PCD8544_send_command(display_norm);
                    break;
                case 3:
                    cursor_index = 0;
                    homeLayout();
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }

            _delay_ms(300);
        }
        if(bit_is_clear(BUTTON_UP_PINR, BUTTON_UP_PIN))
        {
            UART_Send_String("UP\n");
            if(cursor_index > 0)
            {
                set_x_y(0,cursor_index);
                PCD8544_send_char(' ');
                set_x_y(0,--cursor_index);
                PCD8544_send_char('>');
            }
            else
            {
                set_x_y(0,cursor_index);
                PCD8544_send_char(' ');
                cursor_index = 5;
                set_x_y(0,cursor_index);
                PCD8544_send_char('>');
            }
            _delay_ms(300);
        }
        if(bit_is_clear(BUTTON_LEFT_PINR, BUTTON_LEFT_PIN))
        {
            UART_Send_String("Left\n");
            if(contrast > 0x40)
                {
                    PCD8544_send_command(--contrast);
                }
                else
                {
                    contrast = 0x50;
                    PCD8544_send_command(contrast);
                }
            _delay_ms(300);
        }
    }

    return 0;
}

void progressBar(uint8_t x, uint8_t y)
{
    set_x_y(x, y);
    uint8_t length = 0;
    for(length = 0; length < 100; length++)
    {
        PCD8544_send_data(1);
    }
}

void homeLayout(void)
{
    screenIndex = HOME_LAYOUT;
    PCD8544_RAM_Clear();
    set_x_y(0,0);
    PCD8544_send_char('>');
    set_x_y(7,0);
    PCD8544_send_string("I = 1.00A");
    set_x_y(7,1);
    PCD8544_send_string("V = ");
    adcRead = MCP3202_read(1);
    itoa(adcRead, adcStr, 10);
    set_x_y(40,1);
    PCD8544_send_string(adcStr);
    set_x_y(7,2);
    PCD8544_send_string("P = 12.0W");
    set_x_y(7,3);
    PCD8544_send_string("Line 4");
    set_x_y(7,4);
    PCD8544_send_string("Line 5");
    set_x_y(7,5);
    PCD8544_send_string("LCD setup");
}

void lcdSetupLayout(void)
{
    screenIndex = LCD_SETUP_LAYOUT;
    PCD8544_RAM_Clear();
    set_x_y(0,0);
    PCD8544_send_char('>');
    set_x_y(7,0);
    PCD8544_send_string("VID_INV");
    set_x_y(7,1);
    PCD8544_send_string("VID_NORM");
    set_x_y(7,2);
    PCD8544_send_string("Contrast: +-");
    set_x_y(7,3);
    PCD8544_send_string("back");
}
