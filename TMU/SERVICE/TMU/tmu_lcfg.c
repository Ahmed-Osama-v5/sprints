/*
 * tmu_lcfg.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "tmu_lcfg.h"

/*- LOCAL MACROS ------------------------------------------*/

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/

/*- GLOBAL STATIC VARIABLES -------------------------------*/

/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/* Create instance of TMU configuration structure */
/* Assign Timer channel and resolution in mS */
gstrTMUConfig_t gstr_TMUConfig_s = {TIMER_CH0, 1};

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
