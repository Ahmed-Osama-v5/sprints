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
#include "adc_mcp3202.h"
#include "uart.h"
#include "i2c.h"
#include "rtc.h"
#include "ext_eep.h"
#include "pwm.h"
#include "config.h"
#include "keypad.h"

#define NOKIA_5110_LCD
//#define CHAR_LCD

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

typedef enum{RUN, OFFSET_CAL, FULL_SCALE_CAL, GAIN_CAL} State_t;

#define FAN_CTRL        PINB0

#define ADC_CURRENT_CH	0
#define ADC_VOLT_CH		1
#define ADC_REF			5.0
#define VOLTAGE_DIVIDER	5.7143

#define PWM_OFFSET	0.005
#define MAX_DUTY	84

/***********************
 *  Global variables
 ***********************/
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
uint8_t str_number[6], volt_str[6], current_str[6], power_str[6], duty_str[4];

uint8_t duty = 0;
float pwm_Voltage = 0.0;

/***********************
 *  Function prototype
 ***********************/
void adc_Read_Volt(void);
void adc_Read_Current(void);
void adc_Power_Calc(void);
void u16_to_str(uint16_t data, uint8_t *str);

#ifdef NOKIA_5110_LCD
void progressBar(uint8_t x, uint8_t y);
#endif // NOKIA_5110_LCD

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

    PWM2_Start();


    while(1)
    {
    	switch(MCU_State){
    	case RUN:
    		/* Run screen */
			#ifdef NOKIA_5110_LCD
    		NokiaLCD_goto_x_y(0,0);
    		NokiaLCD_send_string("RUN");
			NokiaLCD_goto_x_y(0,1);
			NokiaLCD_send_string("V :");
			NokiaLCD_goto_x_y(0,2);
			NokiaLCD_send_string("I :");
			NokiaLCD_goto_x_y(0,3);
			NokiaLCD_send_string("D :");
			NokiaLCD_goto_x_y(0,4);
			NokiaLCD_send_string("G :");
			NokiaLCD_goto_x_y(0,5);
			NokiaLCD_send_string("O :");
			#endif // NOKIA_5110_LCD

    		adc_Read_Volt();
    		_delay_ms(100);
    		adc_Read_Current();
    		_delay_ms(100);

			if(GetKeyPressed() != NO_KEY_PRESSED){
				if(GetKeyPressed() == OK){
					NokiaLCD_Clear();
					MCU_State = OFFSET_CAL;
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
			u16_to_str((uint16_t)duty, duty_str);
			#ifdef NOKIA_5110_LCD
			NokiaLCD_goto_x_y(35,3);
			NokiaLCD_send_string(duty_str);
			#endif // NOKIA_5110_LCD

			u16_to_str((uint16_t)MCP3202_read(ADC_VOLT_CH), str_number);
			#ifdef NOKIA_5110_LCD
			NokiaLCD_goto_x_y(35,4);
			NokiaLCD_send_string(str_number);
			#endif // NOKIA_5110_LCD

			u16_to_str((uint16_t)MCP3202_read(ADC_CURRENT_CH), str_number);
			#ifdef NOKIA_5110_LCD
			NokiaLCD_goto_x_y(35,5);
			NokiaLCD_send_string(str_number);
			#endif // NOKIA_5110_LCD

			#ifdef CHAR_LCD

			#endif // CHAR_LCD

    		break;
    	case OFFSET_CAL:
    		/* This method is done by feeding 0 volts to the input
    		 * then press (left) key and the MCU will read
    		 * current value and stores it in the adc_offset variable
    		 *  */
			#ifdef NOKIA_5110_LCD
    		NokiaLCD_goto_x_y(0,0);
    		NokiaLCD_send_string("OFFSET_CAL");
			#endif

			#ifdef CHAR_LCD

			#endif // CHAR_LCD

    		if(GetKeyPressed() != NO_KEY_PRESSED){
				switch(GetKeyPressed()){
				case UP:
					break;
				case DOWN:
					break;
				case RIGHT:
					NokiaLCD_Clear();
					MCU_State = RUN;
					break;
				case LEFT:

					adc_offset = MCP3202_read(ADC_VOLT_CH);
					NokiaLCD_Clear();
					MCU_State = FULL_SCALE_CAL;
					break;
				case OK:
					break;
				}
			}
    		break;

    	case FULL_SCALE_CAL:
		/* This method is done by feeding 12.00 volts to the input
		 * then press (left) key and the MCU will calibrate ADC_FULL_SCALE
		 * and return to RUN state
		 *  */
			#ifdef NOKIA_5110_LCD
    		NokiaLCD_goto_x_y(0,0);
    		NokiaLCD_send_string("FULL_SCL_CAL");
			#endif

		#ifdef CHAR_LCD

		#endif // CHAR_LCD

		if(GetKeyPressed() != NO_KEY_PRESSED){
			switch(GetKeyPressed()){
			case UP:
				break;
			case DOWN:
				break;
			case RIGHT:
				break;
			case LEFT:

				ADC_FULL_SCALE = MCP3202_read(ADC_VOLT_CH);
				NokiaLCD_Clear();
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

		u16_to_str((uint16_t)voltage, volt_str);

		#ifdef NOKIA_5110_LCD
		NokiaLCD_goto_x_y(35,1);
		NokiaLCD_send_string(volt_str);
		NokiaLCD_send_char('V');
		#endif // NOKIA_5110_LCD

		#ifdef CHAR_LCD

		#endif // CHAR_LCD
			/*
		if(voltage > MAX_VOLTAGE){
			#ifdef NOKIA_5110_LCD
			NokiaLCD_goto_x_y(35,0);
			NokiaLCD_send_string("OL    ");
			#endif // NOKIA_5110_LCD

			#ifdef CHAR_LCD

			#endif // CHAR_LCD
		}*/
}

void adc_Read_Current(void){
	/* Current measure */
	adcRead = MCP3202_read(ADC_CURRENT_CH) - adc_offset;
	current = ((adcRead * ADC_REF) / ADC_FULL_SCALE) * adc_gain;
	current *= 100;
	u16_to_str((uint16_t)current, current_str);
	#ifdef NOKIA_5110_LCD
    NokiaLCD_goto_x_y(35,2);
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
	u16_to_str((uint16_t)power, power_str);

	#ifdef NOKIA_5110_LCD
    NokiaLCD_goto_x_y(35,4);
	NokiaLCD_send_string(power_str);
	NokiaLCD_send_char('W');
	#endif // NOKIA_5110_LCD

	#ifdef CHAR_LCD

	#endif // CHAR_LCD
}

void u16_to_str(uint16_t data, uint8_t str[]){
	str[0] = (data / 1000) + 48; // Tens
	str[1] = ((data / 100) % 10) + 48; // Ones
	//str[2] = '.'; // Decimal point
	str[2] = ((data / 10) % 10) + 48; // hundredth
	str[3] = (data % 10) + 48; // tenth
}
