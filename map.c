#include "map.h"

map_iterator* map_begin(map *m)
{
	return m->s->head->next[0];
}

map_iterator* map_next(map_iterator *i)
{
	return i->next[0];
}

map* map_init(int (*compare)(const void *a, const void *b))
{
	map *m = malloc(sizeof(map));

	if(!m)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	m->s = skip_list_init(compare);

	return m;
}

void map_add(map *m, void *key, void *value)
{
	pair *p;

	p = pair_init(key, value);
	
	if(!skip_list_contains(m->s, p))
	{
		skip_list_insert(m->s, p);
	}
	else
	{
		pair_free(p);
	}
}

pair* map_remove(map *m, void *key)
{
	pair *p;
	pair *o;

	p = pair_init(key, 0);
	o = skip_list_delete(m->s, p);

	pair_free(p);

	return o;
}

void* map_get(map *m, void *key)
{
	pair *p;
	pair *o;

	p = pair_init(key, 0);

	o = skip_list_find(m->s, p);

	p = pair_free(p);

	if(o)
		return o->second;
	else
		return 0;
}

int map_contains(map *m, void *key)
{
	pair *p;
	int f;

	p = pair_init(key, 0);
	f = skip_list_contains(m->s, p);
	pair_free(p);
	
	return f;
}

void map_keys(map *m, vector *v)
{
	map_iterator *i;

	for(i = map_begin(m); i; i = map_next(i))
		vector_append(v, ((pair *)(i->data))->first);
}

map* map_free(map *m)
{
	pair *t;
	skip_node *n;
	
	n = m->s->head;

	while(n)
	{
		t = n->data;
		pair_free(t);
		n = n->next[0];
	}

	skip_list_free(m->s);
	free(m);

	return 0;
}
