/*
 * linkedList.c
 *
 *  Created on: Dec 19, 2019
 *      Author: Ahmed
 */


#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int isListEmpty(ST_list *list){
	return (list->listSize == 0);
}

char createList(ST_list *list){
	list->head = NULL;
	list->listSize = 0;
	return list->listSize;
}

int insertToList(ST_list *list, unsigned char position, int data){
	ST_node *ptr, *q;
	int i;
	if((ptr = (ST_node *) malloc(sizeof(ST_node)))){
		ptr->data = data;
		ptr->nextNode = NULL;
		if(position == 0){
			ptr->nextNode = list->head;
			list->head = ptr;
		}
		else{
			for(q=list->head, i=0;i<position-1;i++)
				q=q->nextNode;
			ptr->nextNode = q->nextNode;
			q->nextNode = ptr;
		}
		list->listSize++;
		return 1;
	}
	else
		return 0;
}

int deleteFromList(ST_list *list, unsigned char position, int* data){
	ST_node *ptr, *q;
	int i;
	if(position >= list->listSize)
		return 0;
	else{
		if(position == 0){
			*data = list->head->data;
			q = list->head->nextNode;
			free(list->head);
			list->head = q;
		}
		else{
			for(q=list->head, i=0;i<position-1;i++)
				q = q->nextNode;
			*data = q->nextNode->data;
			ptr = q->nextNode->nextNode;
			free(q->nextNode);
			q->nextNode = ptr;
		}
	}
	list->listSize--;
	return 1;
}

ST_node* searchIntoList(ST_list *list, int data){
	ST_node *ptr;
	ptr = list->head;
	while(ptr != NULL){
		if(ptr->data == data)
			return ptr;
		ptr = ptr->nextNode;
	}
	return 0;
}

void sortList(ST_list *list){
	ST_node *ptr, *q, *tmp;
	ptr = list->head;
#ifdef DEBUG_
printf("Sorting list\n");
printf("ptr = %d\n", ptr->data);
#endif // DEBUG_
	if(ptr != NULL){
		int i = 0, j = 0, pos = 0, x;;
		for(i=0;i<list->listSize;i++){
			for(j=0;j<list->listSize-1;j++){
				if(ptr->nextNode == NULL)
					continue;
				if(ptr->data > ptr->nextNode->data){
#ifdef DEBUG_
					printf("Swapping...\n");
#endif // DEBUG_
					// do swap
					q = ptr->nextNode;
#ifdef DEBUG_
					printf("q = %d\n", q->data);
#endif // DEBUG_
					for(tmp=list->head, x=0;x<pos-1;x++)
						tmp = tmp->nextNode;
#ifdef DEBUG_
					printf("tmp = %d\n", tmp->data);
#endif // DEBUG_
					tmp->nextNode = ptr->nextNode;
#ifdef DEBUG_
					printf("tmp = %d\n", tmp->data);
#endif // DEBUG_
					ptr->nextNode = q->nextNode;
#ifdef DEBUG_
					printf("ptr = %d\n", ptr->data);
#endif // DEBUG_
					q->nextNode = ptr;
#ifdef DEBUG_
					printf("q = %d\n", q->data);
#endif // DEBUG_
				}
				else{
					ptr = ptr->nextNode;
#ifdef DEBUG_
					printf("Increase position to %d\nptr = %d\n", pos+1, ptr->data);
#endif // DEBUG_
					pos++;
				}
			}
		}

	}
}

void reverseList(ST_list *list){

}
