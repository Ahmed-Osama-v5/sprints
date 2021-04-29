/*
 * dac8760.c
 *
 *  Created on: Mar 13, 2021
 *      Author: engah
 */

#include "std_types.h"
#include "DAC8760.h"
#include "spi.h"
#include "softwareDelay.h"

void DAC8760_Init(Dac_OutputRange_TypeDef outputRange)
{

	DIO_Cfg_s str_Dio = {0};
	str_Dio.GPIO = DAC_LATCH_PORT;
	str_Dio.dir = OUTPUT;
	str_Dio.pins = DAC_LATCH_PIN;
	DIO_init(&str_Dio);

    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
    SwDelay_ms(1);

    SPI_Cfg_s str_SPI = {0};
    str_SPI.CBK_Func = NULL;
    str_SPI.SPI_DataMode = SPI_MODE_0;
    str_SPI.SPI_DataOrder = SPI_MSB;
    str_SPI.SPI_InterruptMode = SPI_PULLING;
    str_SPI.SPI_Mode = SPI_MASTER;
    str_SPI.SPI_Prescaler = SPI_PRESCALER_128;
    SPI_Init(&str_SPI);

    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
    SwDelay_ms(1);

    uint8 data[2];
    data[0] = 0x01;
    data[1] = 0x00;

    SPI_memTransmit(RESET_REG, data, 2);
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
    SwDelay_ms(1);
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);

/*
    data[0] = 0x00;
    data[1] = 0x80;
    SPI_memTransmit(GAIN_CAL_REG, data, 2);

    data[0] = 0x9C;
    data[1] = 0x06;
    SPI_memTransmit(OFFSET_CAL_REG, data, 2);
*/
    data[0] = 0x00;
    data[1] = 0x00;
    SPI_memTransmit(DATA_REG, data, 2);
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
    SwDelay_ms(1);
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);


    switch(outputRange)
    {
    case (RANGE_0_5_v):
        data[0] = 0x00;
        break;
    case (RANGE_0_10_v):
        data[0] = 0x01;
        break;
    case (RANGE_pos_neg_5_v):
        data[0] = 0x02;
        break;
    case (RANGE_pos_neg_10_v):
        data[0] = 0x03;
        break;
    case (RANGE_4_20_MA):
        data[0] = 0x05;
        break;
    case (RANGE_0_20_MA):
        data[0] = 0x06;
        break;
    case (RANGE_0_24_MA):
        data[0] = 0x07;
        break;
    default:
        break;
    }
    data[1] = 0x10;
    SPI_memTransmit(CTRL_REG, data, 2);
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
    SwDelay_ms(1);
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);

}

void DAC8760_Write(uint8 regAdd, uint16 data)
{
    uint8 tmp[2];
    tmp[0] = (uint8)data;
    tmp[1] = ((uint8)(data >> 8));
    SPI_memTransmit(regAdd, tmp, 2);
}

uint16 DAC8760_Read(uint8 regAdd)
{
	uint8 highByte = 0, lowByte = 0;
	uint16 tmp = regAdd;

	/* Send ReadReg(0x02) byte */
	/* Send RegToBeRead(highByte) */
	/* Send RegToBeRead(lowByte) */
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
	DAC8760_Write(READ_REG, tmp);
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
    SwDelay_ms(1);

	/* Send Nop operation */
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, LOW);
	SPI_SendByte(NOP_REG);
    while(! (SPSR & SPIF));
	/* Receive don't care byte */
	SPI_ReceiveByte(&lowByte);
	/* Receive high byte */
	SPI_SendByte(NOP_REG);
    while(! (SPSR & SPIF));
	SPI_ReceiveByte(&highByte);
	/* Receive low byte */
	SPI_SendByte(NOP_REG);
    while(! (SPSR & SPIF));
	SPI_ReceiveByte(&lowByte);
    DIO_Write(DAC_LATCH_PORT, DAC_LATCH_PIN, HIGH);
    SwDelay_ms(1);

	return((highByte << 8) | lowByte);
}

