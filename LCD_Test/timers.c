/*
 * timers.c
 *
 *  Created on: Dec 6, 2019
 *      Author: Ahmed Osama
 */

#include "std_types.h"
#include "registers.h"
#include "timers.h"

static En_timer0perscaler_t gen_T0_prescale = T0_NO_CLOCK;
static En_timer0Mode_t gen_T0_mode;

static En_timer1perscaler_t gen_T1_prescale = T1_NO_CLOCK;
static En_timer1Mode_t gen_T1_mode;

typedef enum En_timer1Freq_t{
	FREQ_16_M = 16000000,
	FREQ_2_M = 2000000,
	FREQ_250_K = 250000,
	FREQ_62_5_K = 62500,
	FREQ_15_625_K = 15625
}En_timer1Freq_t;

static En_timer1Freq_t gen_T1_Freq;
/*===========================Timer0 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer0Init(En_timer0Mode_t mode,En_timer0OC_t OC0,En_timer0perscaler_t prescal, uint8 initialValue, uint8 outputCompare, En_timer0Interrupt_t interruptMask){
	gen_T0_prescale = prescal;
	gen_T0_mode = mode;
	TCCR0 |= (mode | OC0);
	TCNT0 = initialValue;
	OCR0 = outputCompare;
	TIMSK |= interruptMask;
}

/**
 * Description:
 * @param value
 */
void timer0Set(uint8 value){
	TCNT0 = value;
}

/**
 * Description:
 * @return
 */
uint8 timer0Read(void){
	return TCNT0;
}

/**
 * Description:
 */
void timer0Start(void){
	TCCR0 |= gen_T0_prescale;
}

/**
 * Description:
 */
void timer0Stop(void){
	TCCR0 &= ~((1 << 2) | (1 << 1) | (1 << 0));
}

/**
 * Description:
 * @param delay
 */
void timer0Delay_ms(uint16 delay){
	// Tick interval = 4 uS @ 16 MHz DIV_BY_64
	// 1 mS = 250 ticks.
	uint16 i;
	switch(gen_T0_mode){
	case (T0_NORMAL_MODE):
		timer0Start();
		for(i=0;i<delay;i++){
			timer0Set(6); // Pre-load with 6 counts
			while(!(TIFR & (1 << 0)));
			TIFR |= (1 << 0);
		}
		timer0Stop();
		break;
	case (T0_COMP_MODE):
		OCR0 = 249;
		timer0Start();
		for(i=0;i<delay;i++){
			while(!(TIFR & (1 << 1)));
			TIFR |= (1 << 1);
		}
		timer0Stop();
		break;
	}
}

/**
 * Description:
 * @param dutyCycle
 */
void timer0SwPWM(uint8 dutyCycle,uint8 freq){

}









/*===========================Timer1 Control===============================*/
/**
 * Description:
 * @param controlA
 * @param controlB
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer1Init(En_timer1Mode_t mode,En_timer1OC_t OC,En_timer1perscaler_t prescal, uint16 initialValue, uint16 outputCompareA, uint16 outputCompareB,uint16 inputCapture, En_timer1Interrupt_t interruptMask){
	gen_T1_mode = mode;
	TCCR1 |= (mode | OC);
	gen_T1_prescale = prescal;
	TCNT1 = initialValue;
	switch (gen_T1_prescale) {
		case (T1_PRESCALER_NO):
			gen_T1_Freq = FREQ_16_M;
			break;
		case (T1_PRESCALER_8):
			gen_T1_Freq = FREQ_2_M;
			break;
		case (T1_PRESCALER_64):
			gen_T1_Freq = FREQ_250_K;
			break;
		case (T1_PRESCALER_256):
			gen_T1_Freq = FREQ_62_5_K;
			break;
		case (T1_PRESCALER_1024):
			gen_T1_Freq = FREQ_15_625_K;
			break;
		default:
			break;
	}
	OCR1A = outputCompareA;
	OCR1B = outputCompareB;
	ICR1 = inputCapture;
	TIMSK |= interruptMask;
}

/**
 * Description:
 * @param value
 */
void timer1Set(uint16 value){
	TCNT1 = value;
}

/**
 * Description:
 * @return
 */
uint16 timer1Read(void){
	return TCNT1;
}

/**
 * Description:
 */
void timer1Start(void){
	TCCR1B |= gen_T1_prescale;
}

/**
 * Description:
 */
void timer1Stop(void){
	TCCR1B &= ~((1 << 2) | (1 << 1) | (1 << 0));
}

/**
 * Description:
 * @param delay
 */
void timer1Delay_ms(uint16 delay){
	// Tick interval = 4 uS @ 16 MHz DIV_BY_64
	// 1 mS = 250 ticks.
	uint16 i;
	switch(gen_T1_mode){
	case (T1_NORMAL_MODE):
		timer1Start();
		for(i=0;i<delay;i++){
			timer1Set(65286); // Pre-load with 6 counts
			while(!(TIFR & (1 << 2)));
			TIFR |= (1 << 2);
		}
		timer1Stop();
		break;
	case (T1_COMP_MODE_OCR1A_TOP):
		OCR1A = 249;
		timer1Start();
		for(i=0;i<delay;i++){
			while(!(TIFR & (1 << 4)));
			TIFR |= (1 << 4);
		}
		timer1Stop();
		break;
	case (T1_COMP_MODE_ICR1_TOP):
		ICR1 = 249;
		timer1Start();
		for(i=0;i<delay;i++){
			while(!(TIFR & (1 << 5)));
			TIFR |= (1 << 5);
		}
		timer1Stop();
		break;
	default:
		break;
	}
}

/**
 * Description:
 * @param dutyCycle
 */
void timer1SwPWM(uint8 dutyCycle,uint8 freq){
	/* Calculating frequency */
	//uint16 f = freq * 1000;
	uint16 tcntMax = (uint16)(gen_T1_Freq / freq);
	TCNT1 = 65535 - tcntMax;

	/* Calculating Duty */
	OCR1A = (uint16)((65535 - tcntMax) * ((float)dutyCycle/100.0));
	//OCR1A = ((uint16)((65536 - TCNT1) * ((float)dutyCycle/100.0))) + TCNT1;
	/* wait until compare match occurs */
	while(!(TIFR & (1 << 4)));
	TIFR |= (1 << 4);
	gpioPinWrite(GPIOB, BIT4, LOW);

	/* wait until overflow occurs */
	while(!(TIFR & (1 << 2)));
	TIFR |= (1 << 2);
	gpioPinWrite(GPIOB, BIT4, HIGH);
}






/*===========================Timer2 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer2Init(En_timer2Mode_t mode,En_timer2OC_t OC,En_timer2perscaler_t prescal, uint8 initialValue, uint8 outputCompare, uint8 assynchronous, En_timer2Interrupt_t interruptMask){

}
/**
 * Description:
 * @param value
 */
void timer2Set(uint8 value){

}

/**
 * Description:
 * @return
 */
uint8 timer2Read(void){
	return 0;
}

/**
 * Description:
 */
void timer2Start(void){

}

/**
 * Description:
 */
void timer2Stop(void){

}

/**
 * Description:
 * @param delay
 */
void timer2Delay_ms(uint16 delay){

}

/**
 * Description:
 * @param dutyCycle
 */
void timer2SwPWM(uint8 dutyCycle,uint8 freq){

}

/*
 * user defined
 */
void timer2Delay_us(uint32 delay){

}
