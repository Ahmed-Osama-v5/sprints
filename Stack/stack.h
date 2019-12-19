/*
 * stack.h
 *
 *  Created on: Dec 17, 2019
 *      Author: Ahmed
 */

#ifndef STACK_H_
#define STACK_H_

typedef char StackEntry;

typedef struct ST_stackInfo{
	int top;
	StackEntry *entry;
}ST_stackInfo;

/*****  Create.
* Pre : NONE.
* Post: NONE.
*****/
void createStack(ST_stackInfo *info, int size);

/*****  Push.
* Pre : Stack is initialized and not full.
* Post: NONE.
*****/
void push(ST_stackInfo *info, char data);

/*****  POP.
* Pre : Stack is initialized and not empty.
* Post: NONE.
*****/
void pop(ST_stackInfo *info, char* data);

int Stack_Empty(ST_stackInfo *info);

#endif /* STACK_H_ */
