#ifndef _MAP_H
#define _MAP_H

#include <stdlib.h>
#include <stdio.h>

#include "skip_list.h"
#include "pair.h"
#include "vector.h"

typedef struct
{
	skip_list *s;
} map;

typedef skip_node map_iterator;

map_iterator* map_begin(map *m);
map_iterator* map_next(map_iterator *i);
map* map_init(int (*compare)(const void *a, const void *b));
/* Caller responsible for maintaining correct types for key and
 * value. */
void map_add(map *m, void *key, void *value);
/* Returns pair of key and value if pair removed. If not NULL. Copy of
 * pair not made, caller reponsible for copying. */
pair* map_remove(map *m, void *key);
void* map_get(map *m, void *key);
int map_contains(map *m, void *key);
/* Given a vector, this function puts the keys on the vector. You
 * supply the comparison function yourself since the vector and map
 * comparison functions are different. The vector's comparison is like
 * the qsort or bsearch one, but the map one isn't. No copying of keys
 * is done. Only the pointers are copied. */
void map_keys(map *m, vector *v);
/* Returns NULL. Caller responsible for freeing data in map. */
map* map_free(map *m);

#endif
