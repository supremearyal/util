#include "vector.h"

vector* vector_init(int(*compare)(const void *a, const void *b))
{
	vector *v;

	v = malloc(sizeof(vector));

	if(!v)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	v->cap = DEFAULT_VECTOR_CAPACITY;
	v->len = 0;
	v->compare = compare;

	v->arr = malloc(sizeof(void *) * DEFAULT_VECTOR_CAPACITY);

	if(!(v->arr))
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	return v;
}

void vector_shrink(vector *v)
{
	void **tmp;

	v->cap = v->len;

	tmp = realloc(v->arr, v->cap);

	if(!tmp)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	v->arr = tmp;
}

void vector_grow(vector *v)
{
	void **tmp;

	v->cap *= 2;

	tmp = realloc(v->arr, v->cap * sizeof(void *));

	if(!tmp)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	v->arr = tmp;
}

void vector_reset(vector *v)
{
	v->len = 0;
}

int vector_length(vector *v)
{
	return v->len;
}

/* No error checking done for out of bounds. */
void* vector_get(vector *v, int i)
{
	return v->arr[i];
}

void vector_append(vector *v, void *e)
{
	if(v->len >= v->cap)
		vector_grow(v);

	v->arr[v->len++] = e;
}

void vector_append_vector(vector *a, vector *b)
{
	void **tmp;
	int old_len;

	old_len = a->len;

	a->len += b->len;
	a->cap = a->len;
	tmp = realloc(a->arr, sizeof(void *) * a->cap);

	if(!tmp)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	a->arr = tmp;
	memcpy(a->arr + old_len, b->arr, sizeof(void *) * b->len);
}

/* Returns the location of a given an element and the element's
 * groups' compare function. Linear search performed. Return -1 if not
 * found. */
int vector_index(vector *v, void *e)
{
	int i;

	for(i = 0; i < v->len; ++i)
		if(!(v->compare(v->arr + i, &e)))
			return i;

	return -1;
}

/* Sort using quicksort provided. */
void vector_sort(vector* v)
{
	qsort(v->arr, v->len, sizeof(void *), v->compare);
}

/* Returns a pointer to the pointer to wherever data is found, NULL
 * otherwise. MUST run sort before hand in ascending order. Same
 * requirements as bsearch. */
void* vector_search(vector *v, void *data)
{
	return bsearch(&data, v->arr, v->len, sizeof(void *), v->compare);
}

/* Use Fisher Yates shuffle. */
void vector_shuffle(vector *v)
{
	static int seeded = 0;
	int rnd;
	int i;
	void *tmp; /* For swapping. */

	/* Only seed once. */
	if(!seeded)
	{
		seeded = 1;
		srand(time(NULL));
	}

	for(i = v->len - 1; i > 0; --i)
	{
		rnd = rand() % (i + 1);
		tmp = v->arr[i];
		v->arr[i] = v->arr[rnd];
		v->arr[rnd] = tmp;
	}
}

/* Returns NULL so we can do v = vector_free(v). User responsible for
 * freeing constituent elements. */
vector* vector_free(vector *v)
{
	free(v->arr);
	free(v);

	return 0;
}
