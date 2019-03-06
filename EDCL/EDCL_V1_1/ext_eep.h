/*
 * ext_eep.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_EXT_EEP_H_
#define INC_EXT_EEP_H_


#define EE_ADDR_W 0xA0
#define EE_ADDR_R 0xA1

uint8_t EEWriteByte(uint16_t address,uint8_t data);
uint8_t EEReadByte(uint16_t address);
void EE_Erase(void);

#endif /* INC_EXT_EEP_H_ */
