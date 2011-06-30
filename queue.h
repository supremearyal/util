#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

typedef struct
{
	llist *head;
	llist *tail;
} queue;

#define queue_begin(q) (q->tail)
#define queue_end(q) (0)

/* Caller responsible for freeing data. */
queue* queue_init();
void queue_enqueue(queue *q, void *data);
/* Return first item. Caller responsible for freeing data. */
void* queue_dequeue(queue *q);
queue* queue_free(queue *q);
int queue_length(queue *q);

#endif
