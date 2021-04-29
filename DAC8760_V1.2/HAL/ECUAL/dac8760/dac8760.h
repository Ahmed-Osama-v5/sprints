/*
 * dac8760.h
 *
 *  Created on: Mar 13, 2021
 *      Author: engah
 */

#ifndef HAL_ECUAL_DAC8760_H_
#define HAL_ECUAL_DAC8760_H_

#include "std_types.h"
#include "mega8.h"

#define NOP_REG			(0x00)
#define DATA_REG        (0x01)
#define READ_REG        (0x02)
#define CTRL_REG        (0x55)
#define RESET_REG       (0x56)
#define CONFIG_REG      (0x57)
#define GAIN_CAL_REG    (0x58)
#define OFFSET_CAL_REG  (0x59)

#define DAC_LATCH_PORT 	GPIOB
#define DAC_LATCH_PIN 	PIN2

typedef enum
{
    RANGE_0_5_v,
    RANGE_0_10_v,
    RANGE_pos_neg_5_v,
    RANGE_pos_neg_10_v,
	RANGE_NOT_ALLOWED,
    RANGE_4_20_MA,
    RANGE_0_20_MA,
    RANGE_0_24_MA
}Dac_OutputRange_TypeDef;

void DAC8760_Init(Dac_OutputRange_TypeDef outputRange);
void DAC8760_Write(uint8 regAdd, uint16 data);
uint16 DAC8760_Read(uint8 regAdd);

#endif /* HAL_ECUAL_DAC8760_H_ */
