#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_VECTOR_CAPACITY 10

extern void* memcpy (void *dest, const void *src, size_t n);

typedef struct
{
	/* Array of void* pointers each pointing to data. */
	void **arr;
	int cap;
	int len;
	/* Comparison function pointer. */
	int(*compare)(const void *a, const void *b);
} vector;

vector* vector_init(int(*compare)(const void *a, const void *b));
void vector_shrink(vector *v);
void vector_grow(vector *v);
/* Makes length of vector 0 so we can use it without allocating more
 * memory. */
void vector_reset(vector *v);
int vector_length(vector *v);

void* vector_get(vector *v, int i);
/* Returns the location of a given an element and the element's
 * groups' compare function. */
void vector_append(vector *v, void *e);
void vector_append_vector(vector *a, vector *b);
int vector_index(vector *v, void *e);

/* Sort using quicksort provided. */
void vector_sort(vector* v);
/* Returns a pointer to wherever data is found, NULL otherwise. MUST
 * run sort before hand in ascending order. Same requirements as
 * bsearch .*/
void* vector_search(vector *v, void *data);

/* Nice little utility function to shuffle the array. */
void vector_shuffle(vector *v);

/* Returns NULL so we can do v = vector_free(v). */
vector* vector_free(vector *v);

#endif
