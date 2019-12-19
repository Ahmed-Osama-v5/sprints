/*
 * linkedList.h
 *
 *  Created on: Dec 19, 2019
 *      Author: Ahmed
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

//#define DEBUG_

typedef int listkey;

typedef struct ST_node{
	listkey data;
	struct ST_node *nextNode;
}ST_node;

typedef struct ST_list{
	ST_node *head;
	int listSize;
}ST_list;

int isListEmpty(ST_list *list);
char createList(ST_list *list);
int insertToList(ST_list *list, unsigned char position, int data);
int deleteFromList(ST_list *list, unsigned char position, int* data);
ST_node* searchIntoList(ST_list *list, int data);
void sortList(ST_list *list);
void reverseList(ST_list *list);


#endif /* LINKEDLIST_H_ */
