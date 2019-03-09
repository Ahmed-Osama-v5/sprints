/*
 * config.c
 *
 *  Created on: Mar 5, 2019
 *      Author: Ahmed
 */

#include <avr/io.h>
#include "config.h"

void config_IO(void)
{
    BUTTON_UP_DDR &= ~(1 << BUTTON_UP_PIN);
    BUTTON_DOWN_DDR &= ~(1 << BUTTON_DOWN_PIN);
    BUTTON_RIGHT_DDR &= ~(1 << BUTTON_RIGHT_PIN);
    BUTTON_LEFT_DDR &= ~(1 << BUTTON_LEFT_PIN);
    BUTTON_OK_DDR &= ~(1 << BUTTON_OK_PIN);

    SDA_DDR &= ~(1 << SDA_PIN);
    SCL_DDR &= ~(1 << SCL_PIN);

    /* Activating internal Pull-ups */
    BUTTON_UP_PORT |= (1 << BUTTON_UP_PIN);
    BUTTON_DOWN_PORT |= (1 << BUTTON_DOWN_PIN);
    BUTTON_RIGHT_PORT |= (1 << BUTTON_RIGHT_PIN);
    BUTTON_LEFT_PORT |= (1 << BUTTON_LEFT_PIN);
    BUTTON_OK_PORT |= (1 << BUTTON_OK_PIN);

    SDA_PORT |= (1 << SDA_PIN);
    SCL_PORT |= (1 << SCL_PIN);

    FAN_CTRL_DDR |= (1 << FAN_CTRL_PIN); // set as digital output
    FAN_CTRL_PORT &= ~(1 << FAN_CTRL_PIN); // deactivate FAN

    DDRB |= (1 << PINB4); // not letting PB4(SS) floating lets SPI run normally
}

