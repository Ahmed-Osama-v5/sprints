/*
 * std_types.h
 *
 *  Created on: Dec 22, 2019
 *      Author: Khalaf, Zayed & Saad
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*- INCLUDES -----------------------------------------------*/

/*- CONSTANTS ----------------------------------------------*/
#define FALSE 		    0
#define TRUE 		    1

#define LOW  		    0
#define HIGH 		    0xFF

#define ERROR_STATUS        uint8
#define E_OK		    0
#define E_NOK		    1

#define NOT_INITIALIZED	    0
#define INITIALIZED	    1

/*- PRIMITIVE TYPES ----------------------------------------*/
#ifndef NULL
#define NULL		((void *)0)
#endif /* NULL */

typedef unsigned char uint8;
typedef uint8 bool;
typedef unsigned int uint16;
typedef unsigned long int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;
typedef signed long long sint64;
typedef volatile uint8* const reg_type8;
typedef volatile uint16* const reg_type16;
typedef float float32;

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/


#endif /* STD_TYPES_H_ */
