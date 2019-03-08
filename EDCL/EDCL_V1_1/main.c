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
#include "adc_mcp3202.h"
#include "nokia_5110_lcd.h"
#include "uart.h"
#include "i2c.h"
#include "rtc.h"
#include "ext_eep.h"
#include "pwm.h"
#include "config.h"
#include "keypad.h"

typedef enum{RUN, CAL} State_t;

#define FAN_CTRL        PINB0

#define ADC_CURRENT_CH	0
#define ADC_VOLT_CH		1
#define MAX_VOLTAGE		1200.0
#define ADC_REF			5.0
#define ADC_FULL_SCALE	4095.0
#define VOLTAGE_DIVIDER	5.714


void progressBar(uint8_t x, uint8_t y);
void homeLayout(void);
void lcdSetupLayout(void);

uint8_t cursor_index = 0;
uint8_t contrast = LCD_CONTRAST;

uint16_t adcRead = 0;
uint8_t adc_offset = 0;
float adc_gain = 1.0;
float voltage = 0/*, new_voltage = 0.0*/;
char adcStr[5];
char str_number[6], volt_str[6];
//int timOut = 0;

int main(void)
{
	State_t MCU_State = RUN;
    var = 7;
    config_IO();
    UART_init(9600);
    MCP3202_Init();
    I2C_Master_Init();
    PWM0_init();
    UART_Send_String("EDCL V1.0\nBy/ Ahmed Osama\n");

    PCD8544_init();
    //homeLayout();
    EEWriteByte(0, 0xAD);

    while(1)
    {
    	switch(MCU_State){
    	case RUN:
    		adcRead = MCP3202_read(ADC_VOLT_CH) - adc_offset;
			voltage = ((adcRead * ADC_REF) / ADC_FULL_SCALE) * VOLTAGE_DIVIDER * adc_gain;
			voltage *= 100;
			if(voltage <= MAX_VOLTAGE){
				sprintf(str_number, "%04d", (uint16_t)voltage);
				volt_str[0] = str_number[0];
				volt_str[1] = str_number[1];
				volt_str[2] = '.';
				volt_str[3] = str_number[2];
				volt_str[4] = str_number[3];
				set_x_y(35,1);
				PCD8544_send_string(volt_str);
				PCD8544_send_char('V');
			}
			if(voltage > MAX_VOLTAGE){
				set_x_y(35,1);
				PCD8544_send_string("OL    ");
			}
			if(GetKeyPressed() == OK)
				//new_voltage = voltage;
				MCU_State = CAL;
    		break;
    	case CAL:/*
    		set_x_y(35,1);
    		str_number[0] = (new_voltage / 10) + 48;
			str_number[1] = ((uint8_t)new_voltage % 10) + 48;
			str_number[2] = '.';
			str_number[3] = ((uint8_t)(new_voltage * 10) % 10) + 48;
			str_number[4] = ((uint8_t)(new_voltage * 100) % 10) + 48;
    		PCD8544_send_string(str_number);*/
    		if(GetKeyPressed() != NO_KEY_PRESSED){
				set_x_y(10,4);
				switch(GetKeyPressed()){
				case UP:/*
					new_voltage += 0.01;*/
					break;
				case DOWN:/*
					new_voltage -= 0.01;*/
					break;
				case RIGHT:/*
					set_x_y(10,4);
					PCD8544_send_string("OFFSET");
					_delay_ms(500);
					adc_offset = MCP3202_read(ADC_VOLT_CH);*/
					break;
				case LEFT:
					set_x_y(10,4);
					PCD8544_send_string("OFFSET");
					_delay_ms(500);
					adc_offset = MCP3202_read(ADC_VOLT_CH);
					set_x_y(10,4);
					PCD8544_send_string("      ");
					MCU_State = RUN;
					break;
				case OK:/*
					set_x_y(10,4);
					PCD8544_send_string("GAIN");
					_delay_ms(500);
					adc_gain = new_voltage / voltage;*/
					break;
				}
			}
    		break;
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
/*
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
    sprintf(str_number, "Con = %03d", contrast);
    PCD8544_send_string(str_number);
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
*/
