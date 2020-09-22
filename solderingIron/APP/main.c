/*
 * main.c
 *
 *  Created on: Jul 11, 2020
 *      Author: Ahmed Osama
 * Contact: eng.a.osama92@gmail.com
 */

/*- INCLUDES ----------------------------------------------*/
#include "mega8.h"
#include "dio.h"
#include "ADC.h"
#include "externalInterrupt.h"
#include "softwareDelay.h"

/*- LOCAL MACROS ------------------------------------------*/
#define TRIAC_CON_GPIO	GPIOD
#define TRIAC_CON_PIN	PIN2

#define OPTO_GPIO		GPIOD
#define OPTO_PIN		PIN3

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint16 adcValue = 0;
static uint8 detected = 0;
static uint16 value = 3500;
volatile uint8 last_CH1_state = 0;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
void adc_cbk(void)
{
	adcValue = ADC_GetRead();
	double remap = adcValue * 7.715;
	value = (uint16) remap;
	ADCSRA |= ADIF;
}

void ext_int_cbk(void)
{
	/*
	if (PORTD_PIN & PIN3)
	{                             //We make an AND with the pin state register, We verify if pin 8 is HIGH???
		if (last_CH1_state == 0)
		{                        //If the last state was 0, then we have a state change...
			detected = 1;                                  //We haev detected a state change!
		}
		else if (last_CH1_state == 1)
		{                     //If pin 8 is LOW and the last state was HIGH then we have a state change
			detected = 1;                                    //We haev detected a state change!
			last_CH1_state = 0;                               //Store the current state into the last state for the next loop
		}
	}
	*/
	detected = 1;
}

/*- APIs IMPLEMENTATION -----------------------------------*/

int main(void)
{
	/* Configure and initialize ADC */

	ADC_init_Str_TypeDef str_ADC = {0};
	str_ADC.reference = ADC_REF_AVCC;
	str_ADC.interruptMode = ADC_INT_POLLING;
	str_ADC.ADC_CBK = adc_cbk;
	ADC_Init(&str_ADC);


	/* Select ADC channel */
	//ADC_Channel_Select(ADC_CH_0);

	/* Configure and initialize INT1 */
	ExternInt_Cfg_s str_Ext = {0};
	str_Ext.ExternInt_No = EXTRN_INT_1;
	str_Ext.ExternInt_Event = LOGICAL_CHANGE;
	str_Ext.ExternInt_CBF_Ptr = ext_int_cbk;
	ExternInt_Init(&str_Ext);

	/* Configure and initialize Triac control pin */
	DIO_Cfg_s str_Dio = {0};
	str_Dio.GPIO = TRIAC_CON_GPIO;
	str_Dio.dir = OUTPUT;
	str_Dio.pins = TRIAC_CON_PIN;
	DIO_init(&str_Dio);

	sei();
	ADC_StartConversion();
	double remap = 0.0;

	while(1)
	{
		ADC_StartConversion();
		while(ADCSRA & ADSC);
		adcValue = ADC_GetRead();
		remap = adcValue * 7.715;
		value = (uint16) remap;

		if (detected)
		{
		SwDelay_us(500); //This delay controls the power
		DIO_Write(TRIAC_CON_GPIO, TRIAC_CON_PIN, HIGH);
		SwDelay_us(100);
		DIO_Write(TRIAC_CON_GPIO, TRIAC_CON_PIN, LOW);
		detected = 0;
}

	}
	return 0;
}
