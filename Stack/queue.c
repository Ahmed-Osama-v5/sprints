/*
 * queue.c
 *
 *  Created on: Dec 17, 2019
 *      Author: Ahmed
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int isQueueEmpty(ST_queueInfo *info){
	if((info->front == -1) && (info->back == -1)){
		return 1;
	}
	else
		return 0;
}

static int isQueueFull(ST_queueInfo *info){
	if(info->back == sizeof(info->entry)){
		return 1;
	}
	else
		return 0;
}

void createQueue(ST_queueInfo* info, int maxSize){
	info->front = -1;
	info->back = -1;
	info->entry = malloc(maxSize * sizeof(int));
}

void enqueue(ST_queueInfo *info, int data){
	//if(isQueueFull(info))
		//printf("Queue is full\n");
	//else{
		if(isQueueEmpty(info)){
			info->front = 0;
			info->back = 0;
		}
		else
			info->back++;
		info->entry[info->back] = data;
	//}
}

void dequeue(ST_queueInfo *info, int* data){
	if(isQueueEmpty(info)){
		printf("Queue is empty\n");
	}
	else{
		if(info->front == info->back){
			*data = info->entry[info->front];
			info->front = -1;
			info->back = -1;
		}
		else{
			*data = info->entry[info->front++];
		}
	}

}
