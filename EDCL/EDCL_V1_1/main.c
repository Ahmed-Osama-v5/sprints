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
#include "uart.h"
#include "i2c.h"
#include "rtc.h"
#include "ext_eep.h"
#include "pwm.h"
#include "config.h"
#include "keypad.h"

//#define NOKIA_5110_LCD
#define CHAR_LCD

#ifndef CHAR_LCD
	#ifdef NOKIA_5110_LCD
	#include "nokia_5110_lcd.h"
	#endif // NOKIA_5110_LCD
#endif // CHAR_LCD

#ifndef NOKIA_5110_LCD
	#ifdef CHAR_LCD
	#include "char_lcd.h"
	#endif // CHAR_LCD
#endif // NOKIA_5110_LCD

typedef enum{RUN, CAL} State_t;

#define FAN_CTRL        PINB0

#define ADC_CURRENT_CH	0
#define ADC_VOLT_CH		1
#define MAX_VOLTAGE		1200.0
#define ADC_REF			5.0
#define VOLTAGE_DIVIDER	5.7143

#define PWM_OFFSET	0.005
#define MAX_DUTY	84

#ifdef NOKIA_5110_LCD
void progressBar(uint8_t x, uint8_t y);
#endif // NOKIA_5110_LCD


#ifdef NOKIA_5110_LCD
uint8_t cursor_index = 0;
uint8_t contrast = LCD_CONTRAST;
#endif // NOKIA_5110_LCD

float ADC_FULL_SCALE = 4095.0;
uint16_t adcRead = 0;
uint8_t adc_offset = 0;
float adc_gain = 1.0;
float voltage = 0.0, current = 0.0, power = 0.0, temp_Cal = 0.0;
char adcStr[5];
char str_number[6], volt_str[6], current_str[6], power_str[6];

uint8_t duty = 0;
char duty_str[4];
float pwm_Voltage = 0.0;

void adc_Read_Volt(void);
void adc_Read_Current(void);
void adc_Power_Calc(void);

int main(void)
{
	State_t MCU_State = RUN;

	/* Initialization */
    config_IO();
    UART_init(9600);
    MCP3202_Init();
    I2C_Master_Init();

	#ifdef NOKIA_5110_LCD
    NokiaLCD_init();
	#endif // NOKIA_5110_LCD

	#ifdef CHAR_LCD
    LCD_init();
	#endif // CHAR_LCD

    PWM2_init();

    /* Splash screen */
	#ifdef NOKIA_5110_LCD
    NokiaLCD_goto_x_y(0,0);
    NokiaLCD_send_string(" Electronic");
    NokiaLCD_goto_x_y(0,1);
    NokiaLCD_send_string("  DC Load");
    NokiaLCD_goto_x_y(0,2);
    NokiaLCD_send_string("Ver : 1.1");
    _delay_ms(2000);
    NokiaLCD_Clear();
	#endif // NOKIA_5110_LCD

    #ifdef CHAR_LCD

	#endif // CHAR_LCD

    /* Run screen */
	#ifdef NOKIA_5110_LCD
    NokiaLCD_goto_x_y(0,0);
    NokiaLCD_send_string("V :");
    NokiaLCD_goto_x_y(0,1);
    NokiaLCD_send_string("I :");
    NokiaLCD_goto_x_y(0,2);
    NokiaLCD_send_string("D :");
	#endif // NOKIA_5110_LCD

	#ifdef CHAR_LCD

	#endif // CHAR_LCD

    PWM2_Start();


    while(1)
    {
    	switch(MCU_State){
    	case RUN:
    		adc_Read_Volt();
    		_delay_ms(2);
    		adc_Read_Current();
    		_delay_ms(2);
    		//adc_Power_Calc();
			if(GetKeyPressed() != NO_KEY_PRESSED){
				if(GetKeyPressed() == OK){
					temp_Cal = voltage;
					MCU_State = CAL;
				}
				if(GetKeyPressed() == UP){
					if(duty >= MAX_DUTY)
						duty = 0;
					else
						duty++;
					PWM2_Set_Duty(duty);
				}
				if(GetKeyPressed() == DOWN){
					if(duty <= 0)
						duty = MAX_DUTY;
					else
						duty--;
					PWM2_Set_Duty(duty);
				}
			}
			//pwm_Voltage = (duty * 0.02) + PWM_OFFSET;
			//pwm_Voltage *= 1000;
			sprintf(duty_str, "%04d", /*(uint16_t)pwm_Voltage*/duty);
			/*duty_str[0] = str_number[0];
			duty_str[2] = str_number[1];
			duty_str[1] = '.';
			duty_str[3] = str_number[2];*/
			#ifdef NOKIA_5110_LCD
			NokiaLCD_goto_x_y(35,2);
			NokiaLCD_send_string(duty_str);
			#endif // NOKIA_5110_LCD

			#ifdef CHAR_LCD

			#endif // CHAR_LCD

    		break;
    	case CAL:
    		/* This method is done by feeding any voltage value
    		 * and using (up/down) keys to adjust the value
    		 * displayed on the screen to match feed voltage value
    		 * then press (left) key and the MCU will calibrate ADC_FULL_SCALE
    		 * and return to RUN state.
    		 *  */
    		sprintf(str_number, "%04d", (uint16_t)temp_Cal);
			volt_str[0] = str_number[0];
			volt_str[1] = str_number[1];
			volt_str[2] = '.';
			volt_str[3] = str_number[2];
			volt_str[4] = str_number[3];
			#ifdef NOKIA_5110_LCD
			NokiaLCD_goto_x_y(35,0);
			NokiaLCD_send_string(volt_str);
			NokiaLCD_send_char('V');
			#endif // NOKIA_5110_LCD

			#ifdef CHAR_LCD

			#endif // CHAR_LCD

    		if(GetKeyPressed() != NO_KEY_PRESSED){
				switch(GetKeyPressed()){
				case UP:
					temp_Cal += 0.01;
					break;
				case DOWN:
					temp_Cal -= 0.01;
					break;
				case RIGHT:
					break;
				case LEFT:
					adcRead = MCP3202_read(ADC_VOLT_CH) - adc_offset;
					ADC_FULL_SCALE = (adcRead * ADC_REF) / temp_Cal;
					MCU_State = RUN;
					break;
				case OK:
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
	#ifdef NOKIA_5110_LCD
	NokiaLCD_goto_x_y(x, y);
    uint8_t length = 0;
    for(length = 0; length < 100; length++)
    {
    	NokiaLCD_send_data(1);
    }
	#endif // NOKIA_5110_LCD
}

void adc_Read_Volt(void){
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

			#ifdef NOKIA_5110_LCD
			NokiaLCD_goto_x_y(35,0);
			NokiaLCD_send_string(volt_str);
			NokiaLCD_send_char('V');
			#endif // NOKIA_5110_LCD

			#ifdef CHAR_LCD

			#endif // CHAR_LCD
		}
		if(voltage > MAX_VOLTAGE){
			#ifdef NOKIA_5110_LCD
			NokiaLCD_goto_x_y(35,0);
			NokiaLCD_send_string("OL    ");
			#endif // NOKIA_5110_LCD

			#ifdef CHAR_LCD

			#endif // CHAR_LCD
		}
}

void adc_Read_Current(void){
	/* Current measure */
	adcRead = MCP3202_read(ADC_CURRENT_CH) - adc_offset;
	current = ((adcRead * ADC_REF) / ADC_FULL_SCALE) * adc_gain;
	current *= 100;
	sprintf(str_number, "%04d", (uint16_t)current);
	current_str[0] = str_number[0];
	current_str[1] = str_number[1];
	current_str[2] = '.';
	current_str[3] = str_number[2];
	current_str[4] = str_number[3];

	#ifdef NOKIA_5110_LCD
    NokiaLCD_goto_x_y(35,1);
	NokiaLCD_send_string(current_str);
	NokiaLCD_send_char('A');
	#endif // NOKIA_5110_LCD

	#ifdef CHAR_LCD

	#endif // CHAR_LCD
}

void adc_Power_Calc(void){
	/* Power Calc */
	power = voltage * current;
	//power *= 100;
	sprintf(str_number, "%04d", (uint16_t)power);
	power_str[0] = str_number[0];
	power_str[2] = str_number[1];
	power_str[1] = '.';
	power_str[3] = str_number[2];
	power_str[4] = str_number[3];

	#ifdef NOKIA_5110_LCD
    NokiaLCD_goto_x_y(35,3);
	NokiaLCD_send_string(power_str);
	NokiaLCD_send_char('W');
	#endif // NOKIA_5110_LCD

	#ifdef CHAR_LCD

	#endif // CHAR_LCD
}
