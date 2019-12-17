/*
 * main.c
 *
 *  Created on: Dec 17, 2019
 *      Author: Ahmed
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define DATA_STR_AGILE_REQ_1

#ifdef DATA_STR_AGILE_REQ_1

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
