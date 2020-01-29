/*
 * RetVal.h
 *
 *  Created on: Dec 22, 2019
 *      Author: Knight
 */

#ifndef COMMON_RETVAL_H_
#define COMMON_RETVAL_H_

/************************************************************************/
/*			 			 defining error status             		        */
/************************************************************************/

/* error types*/
#define ERROR_STATUS 						sint8

#define ERR_SUCCESS 				    ( 0)

#define ERR_INVALID_ARGU	    	    (-1)
#define ERR_NOT_INITIALIZED 			(-2)
#define ERR_ALREADY_INITIALIZED  		(-3)
#define ERR_NULL_PTR					(-4)
#define ERR_RESOURCE_NOT_FOUND 			(-5)
#define ERR_HW_CONSTRAIN				(-6)
#define ERR_BUFFER_FULL					(-7)
#define ERR_NOT_SUPPORTED				(-8)

/* modules bases */
#define DIO_BASE_ERROR						(-10)
#define EXT_INT_BASE_ERROR					(-20)
#define TIMER_BASE_ERROR					(-30)
#define PWM_BASE_ERROR						(-40)
#define ICU_BASE_ERROR						(-50)
#define UART_BASE_ERROR						(-60)
#define SPI_BASE_ERROR						(-70)
#define TMU_BASE_ERROR						(-80)
#define BCM_BASE_ERROR						(-90)
#define SOS_BASE_ERROR						(-100)
#define KPD_BASE_ERROR						(-110)
#define LCD_BASE_ERROR						(-120)



#endif /* COMMON_RETVAL_H_ */
