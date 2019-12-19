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
//#define DATA_STR_AGILE_REQ_2
//#define DATA_STR_AGILE_REQ_3
//#define DATA_STR_AGILE_REQ_4
#define DATA_STR_AGILE_REQ_5

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
			pop(&stack, &dummy);
#ifdef DEBUG_
			printf("Poped #%d> %c\n", i, expression[i]);
			printf("POP_Top %c\n", stack.entry[stack.top-1]);
#endif // DEBUG_
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

#ifdef DATA_STR_AGILE_REQ_4

#include "stack.h"
#include "queue.h"

long long evaluate(char* expression);

ST_stackInfo stack;
ST_queueInfo queue;

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	createStack(&stack, 10);
	createQueue(&queue, 15);
	char *val = "(1+2*1-2)/1";
	printf("Result > %I64d\n", evaluate(val));

	return 0;
}

long long evaluate(char* expression){
	long long tmp = 0;
	char markTmp = '+';
	int dummy;
	int i = 0;
	while(expression[i] != '\0'){
		if(expression[i] == '('){
			push(&stack, expression[i]);
#ifdef DEBUG_
			printf("Pushed> %c\n", stack.entry[stack.top]);
#endif // DEBUG_
		}
		else if((expression[i] == ')')){
			// Perform operation on elements in the queue
			while(! isQueueEmpty(&queue)){
				dequeue(&queue, &dummy);
#ifdef DEBUG_
				printf("Dequeued> %c\n", (char)dummy);
#endif // DEBUG_
				if((dummy == '+') || (dummy == '-') || (dummy == '*') || (dummy == '/')){
					markTmp = dummy;
#ifdef DEBUG_
				printf("markTmp> %c\n", (char)dummy);
#endif // DEBUG_
				}
				else{
					if(markTmp == '+'){
#ifdef DEBUG_
				printf("tmp(%I64d) + dummy(%d) = ", tmp, dummy-48);
#endif // DEBUG_
						tmp += (dummy-48);
#ifdef DEBUG_
				printf("%I64d\n", tmp);
#endif // DEBUG_
				}
					else if(markTmp == '-'){
						tmp -= (dummy-48);
#ifdef DEBUG_
				printf("tmp> %I64d\n", tmp);
#endif // DEBUG_
				}
					else if(markTmp == '*'){
						tmp *= (dummy-48);
#ifdef DEBUG_
				printf("tmp> %I64d\n", tmp);
#endif // DEBUG_
				}
					else if(markTmp == '/'){
						tmp /= (dummy-48);
#ifdef DEBUG_
				printf("tmp> %I64d\n", tmp);
#endif // DEBUG_
				}
				}
			}
			// pop stack
			pop(&stack, &dummy);
#ifdef DEBUG_
				printf("Popped> %c\n", (char)dummy);
#endif // DEBUG_
		}
		else{
			enqueue(&queue, expression[i]);
#ifdef DEBUG_
				printf("Enqueued> %c\n", expression[i]);
#endif // DEBUG_
		}
		i++;
	}
	while(! isQueueEmpty(&queue)){
		dequeue(&queue, &dummy);
#ifdef DEBUG_
		printf("Dequeued> %c\n", (char)dummy);
#endif // DEBUG_
		if((dummy == '+') || (dummy == '-') || (dummy == '*') || (dummy == '/')){
			markTmp = dummy;
#ifdef DEBUG_
		printf("markTmp> %c\n", (char)dummy);
#endif // DEBUG_
		}
		else{
			if(markTmp == '+'){
#ifdef DEBUG_
		printf("tmp(%I64d) + dummy(%d) = ", tmp, dummy-48);
#endif // DEBUG_
				tmp += (dummy-48);
#ifdef DEBUG_
		printf("%I64d\n", tmp);
#endif // DEBUG_
			}
			else if(markTmp == '-'){
				tmp -= (dummy-48);
#ifdef DEBUG_
		printf("tmp> %I64d\n", tmp);
#endif // DEBUG_
			}
			else if(markTmp == '*'){
				tmp *= (dummy-48);
#ifdef DEBUG_
		printf("tmp> %I64d\n", tmp);
#endif // DEBUG_
			}
			else if(markTmp == '/'){
				tmp /= (dummy-48);
#ifdef DEBUG_
		printf("tmp> %I64d\n", tmp);
#endif // DEBUG_
			}
		}
	}
	return tmp;
}

#endif // DATA_STR_AGILE_REQ_4

#ifdef DATA_STR_AGILE_REQ_5

#include "linkedList.h"

int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	ST_node *node;
	ST_list list;
	createList(&list);
	int data = 1;
	unsigned char pos = 0;
	if(insertToList(&list, pos, data))
		printf("Inserted %d in position %d successfully\n", data, pos);
	else
		printf("Couldn't insert node to list\n");
	pos++;
	data = 7;
	if(insertToList(&list, pos, data))
		printf("Inserted %d in position %d successfully\n", data, pos);
	else
		printf("Couldn't insert node to list\n");
	pos++;
	data = 8;
	if(insertToList(&list, pos, data))
		printf("Inserted %d in position %d successfully\n", data, pos);
	else
		printf("Couldn't insert node to list\n");
	pos++;
	data = 6;
	if(insertToList(&list, pos, data))
		printf("Inserted %d in position %d successfully\n", data, pos);
	else
		printf("Couldn't insert node to list\n");
	pos++;
	data = 4;
	if(insertToList(&list, pos, data))
		printf("Inserted %d in position %d successfully\n", data, pos);
	else
		printf("Couldn't insert node to list\n");
	pos++;
	data = 9;
	if(insertToList(&list, pos, data))
		printf("Inserted %d in position %d successfully\n", data, pos);
	else
		printf("Couldn't insert node to list\n");

	int i;
	ST_node *tmp;
	tmp = list.head;
	for(i=0;i<list.listSize;i++){
		printf("%d\n", tmp->data);
		tmp = tmp->nextNode;
	}
	sortList(&list);
	tmp = list.head;
	for(i=0;i<list.listSize;i++){
		printf("%d\n", tmp->data);
		tmp = tmp->nextNode;
	}

	return 0;
}

#endif // DATA_STR_AGILE_REQ_5
