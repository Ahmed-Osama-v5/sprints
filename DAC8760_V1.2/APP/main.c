/*
 * Project: ATmega project template
 * main.c
 *
 *  Created on: Jan 7, 2021
 *      Author: Ahmed Osama
 * Contact: eng.a.osama92@gmail.com
 */

/*- INCLUDES ----------------------------------------------*/
#include "mega8.h"
#include "dac8760.h"
#include "softwareDelay.h"
#include "dio.h"
#include "spi.h"
#include "char_lcd.h"

/*- LOCAL MACROS ------------------------------------------*/
#define UP_BUTTON_GPIO		GPIOC
#define UP_BUTTON_PIN		PIN5

#define DOWN_BUTTON_GPIO	GPIOC
#define DOWN_BUTTON_PIN		PIN4

#define MENU_BUTTON_GPIO	GPIOC
#define MENU_BUTTON_PIN		PIN2

#define OUT_BUTTON_GPIO		GPIOC
#define OUT_BUTTON_PIN		PIN3

#define BUTTON_DEBOUNCE		(600)

#define DAC_GAIN			(2)

/*- LOCAL Data types --------------------------------------*/
typedef enum
{
	VOLT,
	CURRENT
}MCU_State_TypeDef;

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
void voltLayout(void);
void currentLayout(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/
volatile uint8 outFlag = 0;
static const float vref = 5.0;
double voltValue = 0.0;
float currentValue = 0.0;
uint8 cursorPosition = 0;
float gainError = 0.998;

MCU_State_TypeDef state = VOLT;
/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

void voltLayout(void)
{
    char arr[6];
    arr[1] = ((int)voltValue%10) + 48;
    arr[0] = (voltValue/10) + 48;
    arr[2] = '.';
    arr[3] = ((int)(voltValue*10) % 10) + 48;
    arr[4] = ((int)(voltValue*100) % 10) + 48;
    arr[5] = ((int)(voltValue*1000) % 10) + 48;
    LCD_goto_xy(4, LINE_0);
    uint8 i;
    for(i=0;i<6;i++)
    {
    	LCD_send_char(arr[i]);
    }
}

void currentLayout(void)
{

    char arr[6];
    arr[1] = ((int)voltValue%10) + 48;
    arr[0] = (voltValue/10) + 48;
    arr[2] = '.';
    arr[3] = ((int)(voltValue*10) % 10) + 48;
    arr[4] = ((int)(voltValue*100) % 10) + 48;
    arr[5] = ((int)(voltValue*1000) % 10) + 48;
    LCD_goto_xy(4, LINE_0);
    uint8 i;
    for(i=0;i<6;i++)
    {
    	LCD_send_char(arr[i]);
    }

}

/*- APIs IMPLEMENTATION -----------------------------------*/

int main(void)
{
	//DIO_Cfg_s str_Dio = {0};
	PORTB_DIR |= (1 << 2);
	/* Set select button as input */
	PORTB_DIR &= ~(1 << 1);
	PORTB_DATA |= (1 << 2);
	/* Activate internal pull-up res at select button */
	PORTB_DATA |= (1 << 1);

	PORTC_DIR &= ~((1 << 5) | (1 << 4) | (1 << 3) | (1 << 2));
	PORTC_DATA |= ((1 << 5) | (1 << 4) | (1 << 3) | (1 << 2));


    LCD_init();
	uint16 i = 0;
	uint8 buttonState = HIGH;

    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
    LCD_goto_xy(13, LINE_1);
	LCD_send_string("OFF");

	DIO_Read(GPIOB, PIN1, &buttonState);
	if(buttonState == LOW)
	{
		uint8 tmpData[2];
		tmpData[0] = RANGE_0_10_v;
		tmpData[1] = 0;
	    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
	    DAC8760_Init(RANGE_0_10_v);
	    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
	    SwDelay_ms(1);
	    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
	    SPI_memTransmit(CTRL_REG, tmpData, 2);
	    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);

    	LCD_goto_xy(0, LINE_0);
    	LCD_send_string("V: ");
    	LCD_goto_xy(12, LINE_0);
    	SwDelay_ms(5);
    	LCD_send_string("V");
		voltLayout();
		state = VOLT;
	}
	else
	{
		uint8 tmpData[2];
		tmpData[0] = RANGE_0_24_MA;
		tmpData[1] = 0;
	    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
	    DAC8760_Init(RANGE_0_24_MA);
	    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
	    SwDelay_ms(1);
	    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
	    SPI_memTransmit(CTRL_REG, tmpData, 2);
	    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);

    	LCD_goto_xy(0, LINE_0);
    	LCD_send_string("I: ");
    	LCD_goto_xy(12, LINE_0);
    	SwDelay_ms(5);
    	LCD_send_string("mA");
		currentLayout();
		state = CURRENT;
	}
	while(1)
	{
		LCD_send_command(Cursor_on);
		DIO_Read(UP_BUTTON_GPIO, UP_BUTTON_PIN, &buttonState);
		if(buttonState == LOW)
		{

			if(cursorPosition == 0)
			{
				voltValue += 1.000;
			}
			else if(cursorPosition == 2)
			{
				voltValue += 0.100;
			}
			else if(cursorPosition == 3)
			{
				voltValue += 0.010;
			}
			else if(cursorPosition == 4)
			{
				voltValue += 0.001;
			}
			else
			{
				/* Do nothing */
			}

			if(state == VOLT)
			{
				i = (uint16)(((voltValue * 65535.0)/(DAC_GAIN * vref))*gainError);
				i += 5;
				voltLayout();
			}
			else
			{
				i = (uint16)((voltValue * 65535.0)/24.0);
				currentLayout();
			}

			LCD_goto_xy((cursorPosition+5), LINE_0);

		    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
		    DAC8760_Write(DATA_REG, i);
		    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
		    SwDelay_ms(BUTTON_DEBOUNCE);
		}
		else
		{
			/* Do nothing */
		}
		DIO_Read(DOWN_BUTTON_GPIO, DOWN_BUTTON_PIN, &buttonState);
		if(buttonState == LOW)
		{

			if(cursorPosition == 0)
			{
				voltValue -= 1.000;
			}
			else if(cursorPosition == 2)
			{
				voltValue -= 0.100;
			}
			else if(cursorPosition == 3)
			{
				voltValue -= 0.010;
			}
			else if(cursorPosition == 4)
			{
				voltValue -= 0.001;
			}
			else
			{
				/* Do nothing */
			}

			if(state == VOLT)
			{
				i = (uint16)(((voltValue * 65535.0)/(DAC_GAIN * vref))*gainError);
				i += 5;
				voltLayout();
			}
			else
			{
				i = (uint16)((voltValue * 65535.0)/24.0);
				currentLayout();
			}

			LCD_goto_xy((cursorPosition+5), LINE_0);

		    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
		    DAC8760_Write(DATA_REG, i);
		    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
		    SwDelay_ms(BUTTON_DEBOUNCE);
		}
		else
		{
			/* Do nothing */
		}
		DIO_Read(MENU_BUTTON_GPIO, MENU_BUTTON_PIN, &buttonState);
		if(buttonState == LOW)
		{
			LCD_goto_xy(0, LINE_0);
			LCD_send_string("                ");
		    switch(state)
		    {
		    case VOLT:
		    	LCD_goto_xy(0, LINE_0);
		    	LCD_send_string("V: ");
		    	LCD_goto_xy(12, LINE_0);
		    	SwDelay_ms(5);
		    	LCD_send_string("V");

				voltLayout();

		    	if(cursorPosition <= 3)
		    	{
		    		if(cursorPosition == 0)
		    		{
		    			cursorPosition = 2;
		    		}
		    		else
		    		{
		    			cursorPosition++;
		    		}
		    	}
		    	else
		    	{
		    		cursorPosition = 0;
		    	}
		    	LCD_goto_xy((cursorPosition+5), LINE_0);
		    	break;
		    case CURRENT:
		    	LCD_goto_xy(0, LINE_0);
		    	LCD_send_string("I: ");
		    	LCD_goto_xy(12, LINE_0);
		    	SwDelay_ms(5);
		    	LCD_send_string("mA");

				currentLayout();

		    	if(cursorPosition <= 3)
		    	{
		    		if(cursorPosition == 0)
		    		{
		    			cursorPosition = 2;
		    		}
		    		else
		    		{
		    			cursorPosition++;
		    		}
		    	}
		    	else
		    	{
		    		cursorPosition = 0;
		    	}
		    	LCD_goto_xy((cursorPosition+5), LINE_0);
		    	break;
		    default:
		    	break;
		    }
		    SwDelay_ms(BUTTON_DEBOUNCE);
		}
		else
		{
			/* Do nothing */
		}
		DIO_Read(OUT_BUTTON_GPIO, OUT_BUTTON_PIN, &buttonState);
		if(buttonState == LOW)
		{
		    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
			uint8 data[2];
			if(state == VOLT)
			{
				data[0] = RANGE_0_10_v;
			}
			else
			{
				data[0] = RANGE_0_24_MA;
			}
		    LCD_goto_xy(13, LINE_1);

			if(outFlag == 1)
			{
				outFlag = 0;
				LCD_send_string("OFF");
			    data[1] = 0;
			}
			else
			{
				outFlag = 1;
				LCD_send_string("ON ");
			    data[1] = 0x10;
			}
		    SPI_memTransmit(CTRL_REG, data, 2);
		    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
		    SwDelay_ms(BUTTON_DEBOUNCE);
		}
		else
		{
			/* Do nothing */
		}
	}
	return 0;
}

