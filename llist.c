#include "llist.h"

llist* llist_init()
{
	return 0;
}

llist* llist_push(llist *head, void *data)
{
	llist *l = malloc(sizeof(llist));

	if(!l)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	l->data = data;
	l->next = head;

	return l;
}

/* Returns NULL if given NULL. */
void* llist_pop(llist *head)
{
	llist *temp = 0;
	
	if(head)
	{
		temp = head->next;
		free(head);
	}

	if(temp)
		return temp->data;
	else
		return temp;
}

/* Returns NULL always so its easy to say my_list =
 * free_list(my_list); */
llist* llist_free(llist *head)
{
	llist *temp;
	
	while(head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}

	return 0;
}

/* Returns length of list. */
int llist_length(llist *head)
{
	int len = 0;

	while(head)
	{
		++len;
		head = head->next;
	}

	return len;
}
