/*
 * interrupt.h
 *
 *  Created on: Dec 9, 2019
 *      Author: Ahmed Osama
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "mega8.h"

#define INT0_vect			__vector_1
#define INT1_vect			__vector_2
#define TIMER2_COMP_vect	__vector_3
#define TIMER2_OVF_vect		__vector_4
#define TIMER1_CAPT_vect	__vector_5
#define TIMER1_COMPA_vect	__vector_6
#define TIMER1_COMPB_vect	__vector_7
#define TIMER1_OVF_vect		__vector_8
#define TIMER0_OVF_vect		__vector_9
#define SPI_STC_vect		__vector_10
#define USART_RXC_vect		__vector_11
#define USART_UDRE_vect		__vector_12
#define USART_TXC_vect		__vector_13
#define ADC_vect			__vector_14
#define EE_RDY_vect			__vector_15
#define ANA_COMP_vect		__vector_16
#define TWI_vect			__vector_17
#define SPM_RDY_vect		__vector_18

#define ISR(vector, ...)            \
   void vector (void) __attribute__ ((signal, used, externally_visible)) __VA_ARGS__; \
   void vector (void)

#define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::)

#endif /* INTERRUPT_H_ */
