#ifndef _LLIST_H
#define _LLIST_H

#include <stdio.h>
#include <stdlib.h>

struct _llist
{
	void *data;
	struct _llist *next;
};

typedef struct _llist llist;

/* TODO: Some kind of initializer function. */
llist* llist_init();
/* Push to the back of the list. If list is empty, make sure that the
 * head being passed in NULL. */
llist* llist_push(llist *head, void *data);
/* Pop element from the back. Caller responsible for freeing whatever
 * was in the node containing data (if it was dynamic at all). */
void* llist_pop(llist *head);
/* Again caller responsible for whatever dynamic data (if any) were in
 * the list. */
llist* llist_free(llist *head);

int llist_length(llist *head);
#endif
