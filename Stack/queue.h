/*
 * queue.h
 *
 *  Created on: Dec 17, 2019
 *      Author: Ahmed
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef int QueueEntry;

typedef struct ST_queueInfo{
		QueueEntry front, back;
        QueueEntry *entry;

    }ST_queueInfo;

void createQueue(ST_queueInfo* info, int maxSize);
void enqueue(ST_queueInfo *info, int data);
void dequeue(ST_queueInfo *info, int* data);

int isQueueEmpty(ST_queueInfo *info);

#endif /* QUEUE_H_ */
