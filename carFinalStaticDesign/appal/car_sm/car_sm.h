/*
 * File		: car_sm.h
 * Created	: 12/21/2019 5:56:37 PM
 * Author	: Amr, Abdo
 * Version	: v1.0
 */

/*************************************************************/
/*                     INCLUDES                              */
/*************************************************************/
#ifndef CAR_SM_H_
#define CAR_SM_H_
#include "std_types.h"

/*************************************************************/
/*                     FUNCTIONS DECLARATION                 */
/*************************************************************/

/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 80%",
 * -------------- And initiate steering and ultrasonic functions
*/
ERROR_STATUS Car_SM_Init(void);

/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/
ERROR_STATUS Car_SM_Update(void);

#endif /* CAR_SM_H_ */
