#ifndef _PAIR_H
#define _PAIR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	void *first;
	void *second;
} pair;

pair* pair_init(void *first, void *second);
/* Change first. Caller responsible for managing memory here. */
void pair_set_first(pair *p, void *first);
/* Change second. */
void pair_set_second(pair *p, void *second);
/* Returns NULL so that the caller can do this: p =
 * pair_free(p). Caller responsible for freeing constituents of
 * pair. */
pair* pair_free(pair *p);

#endif
