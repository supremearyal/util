#include "string.h"
#include "vector.h"

#include <stdio.h>

int stcmp(const void *a, const void *b)
{
	return string_cmp(* (string **) a, * (string **) b);
}

int main(int argc, char **argv)
{
	vector *v;
	string *s;
	string **tmp;
	string *sup;
	int i;

	v = vector_init(stcmp);
	sup = string_init_cstring("6");

	while(--argc)
	{
		s = string_init_cstring(argv[argc]);
		vector_append(v, s);
	}

	printf("size: %d\n", v->len);

	printf("---\n");

	/* Print. */
	for(i = 0; i < v->len; ++i)
		string_println(vector_get(v, i));

	printf("---\n");

	/* Sort and print again. */
	vector_sort(v);
	for(i = 0; i < v->len; ++i)
		string_println(vector_get(v, i));

	printf("---\n");

	/* Search for sup. */
	if(vector_index(v, sup) != -1)
		string_print(sup), printf(" found.\n");
	else
		string_print(sup), printf(" not found.\n");

	printf("---\n");

	/* Using bsearch. */
	tmp = vector_search(v, sup);

	if(tmp)
	{
		string_print(*tmp);
		printf(" found using bsearch.\n");
	}
	else
	{
		string_print(sup);
		printf(" bsearch failed.\n");
	}

	printf("---\n");

	/* Shuffle and print again. */
	vector_shuffle(v);

	for(i = 0; i < v->len; ++i)
		string_println(vector_get(v, i));
		
	printf("---\n");

	for(i = 0; i < v->len; ++i)
		string_free(vector_get(v, i));

	string_free(sup);
	vector_free(v);

	return 0;
}
