#include "HwPWM.h"
#include "interrupt.h"

void HwPWM_Init(void){
	TCCR1B |= (1 << 4); // Mode 8 of the timer 1
	TCCR1A |= ((1 << 7) | (1 << 6) | (1 << 5) | (1 << 4));
	TCCR1B |= ((1 << 1) | (1 << 0)); // DIV_BY_64
}

void HwPWM_ChangeWidth(uint8 duty, uint32 frequency){
	uint16 freq = (uint16)(16000000 / (2 * 64 * frequency));
	ICR1 = freq;
	uint16 val = (freq * (float)(duty/100.0));
	OCR1A = ICR1 - val;
	OCR1B = OCR1A;
}
