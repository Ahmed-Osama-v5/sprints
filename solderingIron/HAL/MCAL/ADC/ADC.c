/*
 * ADC.c
 *
 *  Created on: Jan 20, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "mega8.h"
#include "ADC.h"
#include "interrupt.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
void (*ADC_CBK) (void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
void ADC_Init(ADC_init_Str_TypeDef* init_Str)
{
	if(NULL != init_Str)
	{
		if(init_Str->reference == ADC_REF_INTERNAL)
		{
			/* Internal 2.56v reference */
			ADMUX |= (REFS1 | REFS0);
		}
		else if(init_Str->reference == ADC_REF_EXTERNAL)
		{
			/* External AREF pin */
			ADMUX &= ~(REFS1 | REFS0);
		}
		else if(init_Str->reference == ADC_REF_AVCC)
		{
			/* Vref is AVCC */
			ADMUX |= REFS0;
			ADMUX &= ~REFS1;
		}
		else
		{
			/* TODO: handle this error */
		}

		if(init_Str->interruptMode == ADC_INT_POLLING)
		{
			ADCSRA &= ~(ADIE | ADFR);
			init_Str->ADC_CBK = NULL;
		}
		else if(init_Str->interruptMode == ADC_INT_INTERRUPT)
		{
			ADCSRA |= (ADIE | ADFR);
			if(NULL != init_Str->ADC_CBK)
			{
				ADC_CBK = init_Str->ADC_CBK;
			}
			else
			{
				/* TODO: handle this error */
			}

		}
		else
		{
			/* TODO: handle this error */
		}
	}
	/* ADC prescalerDIV_BY_64 */
	ADCSRA |= (ADPS2 | ADPS1);
	ADCSRA &= ~ADPS0;
	/* Enable ADC */
	ADCSRA |= ADEN;
}

void ADC_StartConversion(void)
{
    ADCSRA |= ADSC;
}

void ADC_Channel_Select(ADC_Channel_TypeDef Channel)
{
	/* Select ADC channel */
		if(Channel == ADC_CH_0)
		{
			ADMUX &= ~(MUX3 | MUX2 | MUX1 | MUX0);
		}
		else if((Channel >= ADC_CH_1) && (Channel <= ADC_CH_7))
		{
			ADMUX &= ~(MUX3 | MUX2 | MUX1 | MUX0);
			ADMUX |= (Channel << 0);
		}
		else
		{
			/* TODO: handle this error */
		}
}

uint16 ADC_GetRead(void)
{
	uint8 lower_bits = ADCL;
	uint16 ten_bit_value = (ADCH << 8 | lower_bits);
	return ten_bit_value;
}

ISR(ADC_vect)
{
	if(NULL != ADC_CBK)
	{
		/* Execute CBK */
		ADC_CBK();
	}
	else
	{
		/* Do nothing */
	}
}
