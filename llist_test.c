#include <stdio.h>
#include "llist.h"
#include "string.h"

int main()
{
	llist *l = 0;
	llist *i;
	string *s = string_init();
	string *q = string_init_cstring("quit");

	string_read_line(s);

	while(string_cmp(s, q))
	{
		l = llist_push(l, s);
		
		s = string_init();
		string_read_line(s);
	}

	/* Last string no in the list. */
	string_free(s);

	printf("Printing list from head to tail.\n");

	i = l;
	while(i)
	{
		string_println(i->data);
		/* Free each string after printing. */
		string_free(i->data);
		i = i->next;
	}

	/* Free entire list. */
	l = llist_free(l);

	/* Get rid of quit string. */
	string_free(q);
	
	return 0;
}
