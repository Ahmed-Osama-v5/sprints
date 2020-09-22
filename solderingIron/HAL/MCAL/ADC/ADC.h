/*
 * ADC.h
 *
 *  Created on: Jan 20, 2020
 *      Author: Ahmed Osama
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"

/*- CONSTANTS ----------------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/
typedef enum
{
	ADC_REF_INTERNAL,
	ADC_REF_EXTERNAL,
	ADC_REF_AVCC
}ADC_Ref_TypeDef;

typedef enum
{
	ADC_INT_POLLING,
	ADC_INT_INTERRUPT
}ADC_Interrupt_TypeDef;

typedef enum
{
	ADC_CH_0,
	ADC_CH_1,
	ADC_CH_2,
	ADC_CH_3,
	ADC_CH_4,
	ADC_CH_5,
	ADC_CH_6,
	ADC_CH_7
}ADC_Channel_TypeDef;

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	ADC_Ref_TypeDef reference;
	ADC_Interrupt_TypeDef interruptMode;
	void (*ADC_CBK) (void);
}ADC_init_Str_TypeDef;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
void ADC_Init(ADC_init_Str_TypeDef* init_Str);
void ADC_StartConversion(void);
void ADC_Channel_Select(ADC_Channel_TypeDef Channel);
uint16 ADC_GetRead(void);


#endif /* MCAL_ADC_ADC_H_ */
