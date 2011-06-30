#include <stdio.h>
#include "string.h"
#include "pair.h"
#include "map.h"

int stcmp(const void *a, const void *b)
{
	return string_cmp(((pair *) a)->first, ((pair *) b)->first);
}

int main()
{
	map *m;
	string *k;
	string *v;
	string *q;
	map_iterator *n;
	pair *t;

	m = map_init(stcmp);
	q = string_init_cstring("");
	k = string_init();
	string_read_line(k);

	while(string_cmp(k, q))
	{
		v = string_init();
		string_read_line(v);
		map_add(m, k, v);

		k = string_init();
		string_read_line(k);
	}

	k = string_free(k);

	/* Iterate through map. */
	for(n = map_begin(m); n; n = map_next(n))
	{
		t = n->data;
		string_print(t->first);
		printf(" => ");
		string_println(t->second);
	}

	/* Free map. */
	for(n = map_begin(m); n; n = map_next(n))
	{
		t = n->data;
		string_free(t->first);
		string_free(t->second);
	}

	string_free(q);
	m = map_free(m);

	return 0;
}
