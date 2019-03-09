/*
 * adc_mcp3202.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_ADC_MCP3202_H_
#define INC_ADC_MCP3202_H_

#define ADC_CE_PIN              7
#define ADC_CE_DDR              DDRA
#define ADC_CE_PORT             PORTA

void MCP3202_Init(void);
uint16_t MCP3202_read(uint8_t channel);

void MCP3208_Init(void);
uint16_t MCP3208_read(uint8_t channel, uint8_t sngOrDif);

#endif /* INC_ADC_MCP3202_H_ */
