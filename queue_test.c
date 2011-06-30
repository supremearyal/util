#include <stdio.h>

#include "queue.h"

int main(int argc, char **argv)
{
	queue *q;
	/*llist *h;*/
	void *v;

	q = queue_init();
	
	while(--argc)
	{
		printf("%s\n", argv[argc]);
		queue_enqueue(q, argv[argc]);
	}

	printf("\nSize: %d\n", queue_length(q));

	/*
	for(h = queue_begin(q); h; h = h->next)
		printf("%s\n", (char *)(h->data));
	*/

	while((v = queue_dequeue(q)))
		printf("%s\n", (char *)v);

	q = queue_free(q);

	return 0;
}
