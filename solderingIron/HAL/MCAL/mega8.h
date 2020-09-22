/*
 * mega8.h
 *
 *  Created on: Jul 11, 2020
 *      Author: Ahmed Osama
 */

#ifndef MEGA8_H_
#define MEGA8_H_
#include "std_types.h"

#define _ATMEGA8_

/*
 * General Registers
 */
#define MCUCR		(*((reg_type8)(0x55)))
#define MCUCSR		(*((reg_type8)(0x54)))
#define GICR		(*((reg_type8)(0x5B)))
#define GIFR		(*((reg_type8)(0x5A)))

/**
 * MCUCR bits
 */

#define ISC00	(0x01)
#define ISC01	(0x02)
#define ISC10	(0x04)
#define ISC11	(0x08)
#define SM0		(0x10)
#define SM1		(0x20)
#define SM2		(0x40)
#define SE		(0x80)

/**
 * MCUCSR bits
 */

#define PORF	(0x01)
#define EXTRF	(0x02)
#define BORF	(0x04)
#define WDRF	(0x08)

/**
 * GICR bits
 */

#define IVCE	(0x01)
#define IVSEL	(0x02)
#define INT0	(0x40)
#define INT1	(0x80)

/**
 * GIFR bits
 */

#define INTF0	(0x40)
#define INTF1	(0x80)

/*
 * PORTx registers
 */

#define PORTB_DATA 	(*((reg_type8)(0x38)))
#define PORTB_DIR  	(*((reg_type8)(0x37)))
#define PORTB_PIN	(*((reg_type8)(0x36)))

#define PORTC_DATA 	(*((reg_type8)(0x35)))
#define PORTC_DIR  	(*((reg_type8)(0x34)))
#define PORTC_PIN	(*((reg_type8)(0x33)))


#define PORTD_DATA 	(*((reg_type8)(0x32)))
#define PORTD_DIR  	(*((reg_type8)(0x31)))
#define PORTD_PIN	(*((reg_type8)(0x30)))


/*
 * General Timer registers
 */
#define TIMSK		(*((reg_type8)(0x59)))
#define TIFR		(*((reg_type8)(0x58)))

/**
 * TIMSK bits
 */

#define TOIE0	(0x01)
#define TOIE1	(0x04)
#define OCIE1B	(0x08)
#define OCIE1A	(0x10)
#define TICIE1	(0x20)
#define TOIE2	(0x40)
#define OCIE2	(0x80)

/**
 * TIFR bits
 */

#define TOV0	(0x01)
#define TOV1	(0x04)
#define OCF1B	(0x08)
#define OCF1A	(0x10)
#define ICF1	(0x20)
#define TOV2	(0x40)
#define OCF2	(0x80)


/*
 * Timer 0 Registers
 */

#define TCCR0		(*((reg_type8)(0x53)))
#define TCNT0		(*((reg_type8)(0x52)))

/**
 * TCCR0 bits
 */

#define CS00	(0x01)
#define CS01	(0x02)
#define CS02	(0x04)


/*
 * Timer 1 Registers
 */

#define TCCR1A		(*((reg_type8)(0x4F)))
#define TCCR1B		(*((reg_type8)(0x4E)))
#define TCCR1		(*((reg_type16)(0x4E)))
#define TCNT1H		(*((reg_type8)(0x4D)))
#define TCNT1L		(*((reg_type8)(0x4C)))
#define TCNT1		(*((reg_type16)(0x4C)))
#define OCR1AH		(*((reg_type8)(0x4B)))
#define OCR1AL		(*((reg_type8)(0x4A)))
#define OCR1A		(*((reg_type16)(0x4A)))
#define OCR1BH		(*((reg_type8)(0x49)))
#define OCR1BL		(*((reg_type8)(0x48)))
#define OCR1B		(*((reg_type16)(0x48)))
#define ICR1H		(*((reg_type8)(0x47)))
#define ICR1L		(*((reg_type8)(0x46)))
#define ICR1		(*((reg_type16)(0x46)))

/**
 * TCCR1A bits
 */

#define WGM10	(0x01)
#define WGM11	(0x02)
#define FOC1B	(0x04)
#define FOC1A	(0x08)
#define COM1B0	(0x10)
#define COM1B1	(0x20)
#define COM1A0	(0x40)
#define COM1A1	(0x80)

/**
 * TCCR1B bits
 */

#define CS10	(0x01)
#define CS11	(0x02)
#define CS12	(0x04)
#define WGM12	(0x08)
#define WGM13	(0x10)
#define ICES1	(0x40)
#define ICNC1	(0x80)


/*
 * Timer 2 Registers
 */
#define TCCR2		(*((reg_type8)(0x45)))
#define TCNT2		(*((reg_type8)(0x44)))
#define OCR2		(*((reg_type8)(0x43)))

/**
 * TCCR2 bits
 */

#define CS20	(0x01)
#define CS21	(0x02)
#define CS22	(0x04)
#define WGM21	(0x08)
#define COM20	(0x10)
#define COM21	(0x20)
#define WGM20	(0x40)
#define FOC2	(0x80)


/*
 * ADC Registers
 */
#define ADCL   		(*((reg_type8)(0x24)))
#define ADCH   		(*((reg_type8)(0x25)))
#define ADCSRA   	(*((reg_type8)(0x26)))
#define ADMUX   	(*((reg_type8)(0x27)))

/**
 * ADCSRA bits
 */

#define ADPS0	        (0x01)
#define ADPS1 	        (0x02)
#define ADPS2  	        (0x04)
#define ADIE 	        (0x08)
#define ADIF  	        (0x10)
#define ADFR	        (0x20)
#define ADSC 	        (0x40)
#define ADEN 	        (0x80)

/**
 * ADMUX bits
 */

#define MUX0	        (0x01)
#define MUX1 	        (0x02)
#define MUX2  	        (0x04)
#define MUX3 	        (0x08)
#define ADLAR	        (0x20)
#define REFS0 	        (0x40)
#define REFS1 	        (0x80)


#endif /* MEGA8_H_ */
