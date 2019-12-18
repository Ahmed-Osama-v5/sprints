/*
 * main.c
 *
 *  Created on: Dec 17, 2019
 *      Author: Ahmed
 */

#include <stdio.h>
#include <stdlib.h>

//#define DEBUG_

//#define DATA_STR_AGILE_REQ_1
#define DATA_STR_AGILE_REQ_2
//#define DATA_STR_AGILE_REQ_3

#ifdef DATA_STR_AGILE_REQ_1

#include "stack.h"

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	ST_stackInfo stack;
	int size = 5;
	createStack(&stack, size);

	StackEntry entry[size];

	int i;
	for(i=0;i<size;i++){
		printf("Insert entery #%d>\n", i);
		scanf("%d",&entry[i]);
		push(&stack, entry[i]);
	}
	int data;
	printf("Top> %d\n", stack.top);
	pop(&stack, &data);
	printf("Data> %d\n", data);
	printf("Top> %d\n", stack.top);

	return 0;
}

#endif // DATA_STR_AGILE_REQ_1

#ifdef DATA_STR_AGILE_REQ_2

#include "stack.h"

unsigned char checkForBalancedParantheses(char* expression);

ST_stackInfo stack;
int size = 10;

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	createStack(&stack, size);

	char arrCahrs[20];
	gets(arrCahrs);
	if(checkForBalancedParantheses(arrCahrs))
		printf("Balanced\n");
	else
		printf("Not balanced\n");


	return 0;
}

unsigned char checkForBalancedParantheses(char* expression){
	int i = 0;
	char dummy;
	while(expression[i] != '\0'){
		if((expression[i] == '{') || (expression[i] == '[') || (expression[i] == '(')){
			push(&stack, expression[i]);
#ifdef DEBUG_
			printf("Pushed #%d> %c\n", i, dummy);
			printf("PUSH_Top %c\n", stack.entry[stack.top-1]);
#endif // DEBUG_
		}
		if((expression[i] == ')')){
			if(stack.entry[stack.top-1] == '('){
			pop(&stack, &dummy);
#ifdef DEBUG_
			printf("Poped #%d> %c\n", i, dummy);
			printf("POP_Top %c\n", stack.entry[stack.top-1]);
#endif // DEBUG_
			}
		}
		else if((expression[i] == ']')){
			if(stack.entry[stack.top-1] == '['){
			pop(&stack, &dummy);
#ifdef DEBUG_
			printf("Poped #%d> %c\n", i, dummy);
			printf("POP_Top %c\n", stack.entry[stack.top-1]);
#endif // DEBUG_
			}
		}
		else if((expression[i] == '}')){
			if(stack.entry[stack.top-1] == '{'){
#ifdef DEBUG_
			printf("Poped #%d> %c\n", i, expression[i]);
			printf("POP_Top %c\n", stack.entry[stack.top-1]);
#endif // DEBUG_
				pop(&stack, &dummy);
			}
		}
		i++;
	}
	if(Stack_Empty(&stack))
		return 1;
	else
		return 0;
}

#endif // DATA_STR_AGILE_REQ_2


#ifdef DATA_STR_AGILE_REQ_3

#include "queue.h"


int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	ST_queueInfo queue;
	int size = 5;
	createQueue(&queue, size);

	QueueEntry entry[size];

	int i;
	for(i=0;i<size;i++){
		printf("Insert entery #%d>\n", i);
		scanf("%d",&entry[i]);
		enqueue(&queue, entry[i]);
	}

	int data;
	for(i=0;i<size;i++){
		dequeue(&queue, &data);
		printf("Back #%d> %d\n", i, data);
	}

	return 0;
}

#endif // DATA_STR_AGILE_REQ_3
