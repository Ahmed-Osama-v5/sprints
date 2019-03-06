/*
 * rtc.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_


#define DS1307_ADDR_W 0xD0
#define DS1307_ADDR_R 0xD1

#define SECOND_REGISTER     0X00
#define MINUTE_REGISTER     0X01
#define HOUR_REGISTER       0X02
#define DAY_NUMBER_REGISTER 0X03
#define DAY_REGISTER        0X04
#define MONTH_REGISTER      0X05
#define YEAR_REGISTER       0X06
#define CONTROL_REGISTER    0X07

uint8_t DS1307Read(uint8_t address);
void DS1307Write(uint8_t address,uint8_t data);
uint8_t bcdToDec(uint8_t val);
uint8_t decToBcd(uint8_t val);
void DS1307_set_time(uint8_t second, uint8_t minute, uint8_t hour);
void DS1307_set_date(uint8_t day, uint8_t month, uint8_t year);
void DS1307_read_time(void);
void DS1307_read_date(void);


#endif /* INC_RTC_H_ */
