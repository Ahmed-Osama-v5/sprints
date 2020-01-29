/*
 * Bit_math.h
 *
 *  Created on: Dec 22, 2019
 *      Author: Knight
 */

#ifndef COMMON_BIT_MATH_H_
#define COMMON_BIT_MATH_H_



/************************************************************************/
/*			       			BIT_MATH defines       	                    */
/************************************************************************/

/* Set VARiable's Certin BIT High */

#define SET_BIT(VAR,BIT_NB) 		(VAR)|=(BIT_NB)

/* Set VARiable's Certin BIT Low */

#define CLR_BIT(VAR,BIT_NB) 		(VAR)&=~(BIT_NB)

/* Toggle VARiable's Certin BIT */

#define TOGGLE_BIT(VAR,BIT_NB) 		(VAR)^=(BIT_NB)

/* Assign VARiable's Certin BIT by a Certin VALue */

#define ASSIGN_BIT(VAR,BIT_NB,VAL)  (VAR)=((VAR&(~(BIT_NB)))|((VAL)&(BIT_NB)))

/* Get VARiable's Certin BIT Value */

#define GET_BIT(VAR,BIT_NB) 		(((VAR)&(BIT_NB))/(BIT_NB))



#endif /* COMMON_BIT_MATH_H_ */
