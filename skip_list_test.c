#include <stdio.h>

#include "string.h"
#include "skip_list.h"

int stcmp(const void *a, const void *b)
{
	return string_cmp((string *) a, (string *) b);
}

int main()
{
	skip_list *s;
	skip_node *n;
	string *ss;
	string *q;
	string *f;
	string *x;

	s = skip_list_init(stcmp);
	ss = string_init();
	q = string_init_cstring("");
	string_read_line(ss);

	while(string_cmp(ss, q))
	{
		skip_list_insert(s, ss);

		ss = string_init();
		string_read_line(ss);
	}

	x = string_init_cstring("supreme");

	/* Testing remove function. */
	f = skip_list_delete(s, x);

	if(skip_list_contains(s, x))
		printf("--what?--\n");

	if(f)
		string_free(f);
	
	for(n = s->head->next[0]; n; n = n->next[0])
		string_println(n->data);

	for(n = s->head->next[0]; n; n = n->next[0])
		string_free(n->data);

	string_free(ss);
	string_free(q);
	string_free(x);
	s = skip_list_free(s);

	return 0;
}
