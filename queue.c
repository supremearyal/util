#include "queue.h"

queue* queue_init()
{
	queue *q = malloc(sizeof(queue));

	if(!q)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	q->head = llist_init();
	q->tail = llist_init();

	return q;
}

void queue_enqueue(queue *q, void *data)
{
	llist *l;

	l = llist_init();
	l = llist_push(l, data);

	/* If this is the first node, we have to set tail. */
	if(!(q->tail))
	{
		q->tail = l;
	}
	else
	{
		q->tail->next = l;
		q->tail = q->tail->next;
	}

	/* If this is the first node, we have to set head. */
	if(!(q->head))
		q->head = q->tail;
}

void* queue_dequeue(queue *q)
{
	llist *h = q->head;
	void *v;

	/* If our queue isn't empty. */
	if(h)
	{
		q->head = q->head->next;
		v = h->data;
		free(h);

		return v;
	}
	else
	{
		return 0;
	}
}

/* Caller responsible for deleting individual data elements. */
queue* queue_free(queue *q)
{
	llist *h;
	
	for(h = q->head; h; h = h->next)
		free(h);

	free(q);
	return 0;
}

int queue_length(queue *q)
{
	int len = 0;
	llist *h;

	for(h = q->head; h; h = h->next)
		++len;

	return len;
}
