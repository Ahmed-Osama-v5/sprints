/*
 * timers.c
 *
 *  Created on: Dec 6, 2019
 *      Author: Ahmed Osama
 */

#include "std_types.h"
#include "registers.h"
#include "timers.h"

static En_timer0perscaler_t gen_prescale = T0_NO_CLOCK;

/*===========================Timer0 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer0Init(En_timer0Mode_t mode,En_timer0OC_t OC0,En_timer0perscaler_t prescal, uint8 initialValue, uint8 outputCompare, uint8 interruptMask){
	gen_prescale = prescal;
	TCCR0 |= (mode | OC0);
	TCNT0 = initialValue;
	OCR0 = outputCompare;
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

	TCCR0 |= gen_prescale;
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
	timer0Set(6); // Pre-load with 6 counts
	timer0Start();
	for(i=0;i<delay;i++){
		while(!(TIFR & (1 << 0)));
		TIFR |= (1 << 0);
	}
	timer0Stop();
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
void timer1Init(En_timer1Mode_t mode,En_timer1OC_t OC,En_timer1perscaler_t prescal, uint16 initialValue, uint8 outputCompareLow, uint8 outputCompareHigh,uint16 inputCapture, uint8 interruptMask){

}

/**
 * Description:
 * @param value
 */
void timer1SetA(uint8 value){

}

/**
 * Description:
 * @param value
 */
void timer1SetB(uint8 value){

}

/**
 * Description:
 * @return
 */
uint8 timer1ReadA(void){
	return 0;
}

/**
 * Description:
 * @return
 */
uint8 timer1ReadB(void){
	return 0;
}

/**
 * Description:
 */
void timer1Start(void){

}

/**
 * Description:
 */
void timer1Stop(void){

}

/**
 * Description:
 * @param delay
 */
void timer1Delay_ms(uint16 delay){

}

/**
 * Description:
 * @param dutyCycle
 */
void timer1SwPWM(uint8 dutyCycle,uint8 freq){

}





/*===========================Timer2 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer2Init(En_timer2Mode_t mode,En_timer2OC_t OC,En_timer2perscaler_t prescal, uint8 initialValue, uint8 outputCompare, uint8 assynchronous, uint8 interruptMask){

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
