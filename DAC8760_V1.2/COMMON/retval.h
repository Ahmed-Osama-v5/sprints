/*
 * retval.h
 *
 *  Created on: Jan 13, 2020
 *      Author: Ahmed Osama
 */

#ifndef COMMON_RETVAL_H_
#define COMMON_RETVAL_H_

/*- INCLUDES -----------------------------------------------*/

/*- CONSTANTS ----------------------------------------------*/
/**
*   @brief:  This return value indicate that the function could
*             run successfully and it returns no errors.
*/
#define   SUCCESS                            ( 0 )
/**
*   @brief:  This return value indicate that the selected resource
*           not found in the platform.
*/
#define   ERROR_RESOURCE_UNAVAILABLE           ( -1 )
/**
*   @brief:  This return value indicate that the function tries
*             to use an uninitialized module.
*/
#define   ERROR_NOT_INITIALIZED              ( -2 )
/**
*   @brief:  This return value indicate that the function tries
*             to use a NULL pointer.
*/
#define   ERROR_NULL_POINTER                 ( -3 )

/**
*   @brief:  This return value indicate that the function tries
*             to use an empty array.
*/
#define   ERROR_ARRAY_EMPTY                 ( -4 )


/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/


#endif /* COMMON_RETVAL_H_ */
