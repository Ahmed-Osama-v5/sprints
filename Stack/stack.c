/*
 * stack.c
 *
 *  Created on: Dec 17, 2019
 *      Author: Ahmed
 */

#include <stdlib.h>
#include "stack.h"


/*****  Create.
* Pre : NONE.
* Post: NONE.
*****/
void createStack(ST_stackInfo *info, int size){
	info->top = 0;
	info->entry = malloc(size * sizeof(int));
}

/*****  Push.
* Pre : Stack is initialized and not full.
* Post: NONE.
*****/
void push(ST_stackInfo *info, char data){
	info->entry[info->top++] = data;
}

/*****  POP.
* Pre : Stack is initialized and not empty.
* Post: NONE.
*****/
void pop(ST_stackInfo *info, char* data){
	*data = info->entry[--info->top];
}

int Stack_Empty(ST_stackInfo *info)
{
    return !info->top;
}
