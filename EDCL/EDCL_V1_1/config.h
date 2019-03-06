/*
 * config.h
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#define BUTTON_UP_PIN           6
#define BUTTON_UP_PINR          PINC
#define BUTTON_UP_DDR           DDRC
#define BUTTON_UP_PORT          PORTC

#define BUTTON_DOWN_PIN         4
#define BUTTON_DOWN_PINR        PINC
#define BUTTON_DOWN_DDR         DDRC
#define BUTTON_DOWN_PORT        PORTC

#define BUTTON_RIGHT_PIN        3
#define BUTTON_RIGHT_PINR       PINC
#define BUTTON_RIGHT_DDR        DDRC
#define BUTTON_RIGHT_PORT       PORTC

#define BUTTON_LEFT_PIN         7
#define BUTTON_LEFT_PINR        PINC
#define BUTTON_LEFT_DDR         DDRC
#define BUTTON_LEFT_PORT        PORTC

#define BUTTON_OK_PIN           5
#define BUTTON_OK_PINR          PINC
#define BUTTON_OK_DDR           DDRC
#define BUTTON_OK_PORT          PORTC

#define SDA_PIN                 1
#define SDA_PINR                PINC
#define SDA_DDR                 DDRC
#define SDA_PORT                PORTC

#define SCL_PIN                 0
#define SCL_PINR                PINC
#define SCL_DDR                 DDRC
#define SCL_PORT                PORTC

#define FAN_CTRL_PIN            0
#define FAN_CTRL_PINR           PINB
#define FAN_CTRL_DDR            DDRB
#define FAN_CTRL_PORT           PORTB

#define ADC_CE_PIN              7
#define ADC_CE_PINR             PINA
#define ADC_CE_DDR              DDRA
#define ADC_CE_PORT             PORTA


void config_IO(void);

#endif /* INC_CONFIG_H_ */

