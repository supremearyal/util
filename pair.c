#include "pair.h"

pair* pair_init(void *a, void *b)
{
	pair *p = malloc(sizeof(pair));

	if(!p)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	p->first = a;
	p->second = b;

	return p;
}

void pair_set_first(pair *p, void *first)
{
	p->first = first;
}

void pair_set_second(pair *p, void *second)
{
	p->second = second;
}

pair* pair_free(pair *p)
{
	free(p);

	return NULL;
}
