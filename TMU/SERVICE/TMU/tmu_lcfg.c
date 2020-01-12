/*
 * tmu_lcfg.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

#include "tmu_lcfg.h"

/* Create instance of TMU configuration structure */
/* Assign Timer channel and resolution in mS */
StrTmuConfig_t str_TmuConfig_s = {TMU_TIMER_CH0, 1};
