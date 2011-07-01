#include "string.h"

string* string_init()
{
	string *s = malloc(sizeof(string));

	if(!s)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	s->cap = DEFAULT_STRING_CAPACITY;

	/* The char* memory block is compatible as a cstring. Hence we
	 * have one more space for the NULL terminator. */
	s->str = malloc(sizeof(char) * s->cap);

	if(!(s->str))
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	s->len = 0;

	return s;
}

string* string_init_cstring(char *c)
{
	string *s = string_init();

	while(*c)
	{
		if(s->len >= s->cap)
			string_grow(s);

		s->str[s->len++] = *c;

		++c;
	}

	return s;
}

void string_shrink(string *s)
{
	char *tmp;
	
	if(s->cap > s->len)
	{
		s->cap = s->len;
		tmp = realloc(s->str, s->cap * sizeof(char));

		if(!tmp)
		{
			fprintf(stderr, "Insufficient memory.\n");
			exit(EXIT_FAILURE);
		}

		s->str = tmp;
	}
}

void string_grow(string *s)
{
	char *tmp;
	
	if(s->len >= s->cap)
	{
		s->cap *= 2;
		
		tmp = realloc(s->str, s->cap);

		if(!tmp)
		{
			fprintf(stderr, "Insufficient memory.\n");
			exit(EXIT_FAILURE);
		}

		s->str = tmp;
	}
}

void string_reset(string *s)
{
	s->len = 0;
}

int string_length(string *s)
{
	return s->len;
}

/* Caller responsible for freeing the dynamic cstring returned. */
char* string_to_cstring(string *s)
{
	/* One more for NULL terminator. */
	char* c = malloc(sizeof(char) * (s->len + 1));

	if(!c)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	memcpy(c, s->str, s->len * sizeof(char));
	c[s->len] = 0;

	return c;
}

/* Returns if the user finished line with a newline or ^D. */
int string_read_line(string *s)
{
	int c;

	while((c = getchar()) != EOF && c != '\n')
	{
		if(s->len >= s->cap)
			string_grow(s);

		s->str[s->len++] = c;
	}

	return c;
}

/* Returns if the user finished line with a newline or ^D. */
int string_read_line_stream(FILE *f, string *s)
{
	int c;

	while((c = getc(f)) != EOF && c != '\n')
	{
		if(s->len >= s->cap)
			string_grow(s);

		s->str[s->len++] = c;
	}

	return c;
}

void string_print(string *s)
{
	int i;

	for(i = 0; i < s->len; ++i)
		putchar(s->str[i]);
}

void string_println(string *s)
{
	int i;

	for(i = 0; i < s->len; ++i)
		putchar(s->str[i]);

	putchar('\n');
}

int string_cmp(string *a, string *b)
{
	int ia;
	int ib;

	int lena;
	int lenb;
	int len_diff;

	char *stra;
	char *strb;

	lena = a->len;
	lenb = b->len;
	len_diff = lena - lenb;

	stra = a->str;
	strb = b->str;

	if(len_diff)
		return len_diff;

	for(ia = ib = 0; ia < lena && ib < lenb; ++ia, ++ib)
		if(*stra++ != *strb++)
			return (*--stra) - (*--strb);

	return len_diff;
}

string* string_cat(string *a, string *b)
{
	string *c = malloc(sizeof(string));

	if(!c)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	c->cap = c->len = a->len + b->len;
	c->str = malloc(sizeof(char) * c->cap);

	if(!(c->str))
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	memcpy(c->str, a->str, a->len * sizeof(char));
	memcpy(c->str + a->len, b->str, b->len * sizeof(char));

	return c;
}

string* string_cpy(string *s)
{
	string *c = malloc(sizeof(string));

	if(!c)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	c->cap = c->len = s->len;
	c->str = malloc(sizeof(c->cap));
	if(!(c->str))
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	memcpy(c->str, s->str, s->len * sizeof(char));

	return c;
}

void string_append(string *s, string *o)
{
	char *tmp;
	int old_len;

	old_len = s->len;

	s->len += o->len;
	s->cap = s->len;
	tmp = realloc(s->str, sizeof(char) * s->cap);

	if(!tmp)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	s->str = tmp;

	memcpy(s->str + old_len, o->str, sizeof(char) * o->len);
}

void string_append_cstring(string *s, char *c)
{
	char *tmp;
	int old_len;
	int c_len;

	old_len = s->len;
	c_len = strlen(c);

	s->len += c_len;
	s->cap = s->len;
	tmp = realloc(s->str, sizeof(char) * s->cap);

	if(!tmp)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	s->str = tmp;

	memcpy(s->str + old_len, c, sizeof(char) * c_len);
}

void string_append_char(string *s, char c)
{
	if(s->len >= s->cap)
		string_grow(s);

	s->str[s->len++] = c;
}

/* There is no way to designate out of bounds. Bounds not checked. */
char string_get(string *s, int i)
{
	return s->str[i];
}

/* Returns -1 if string not found. */
int string_index(string *s, char c)
{
	int i;

	for(i = 0; i < s->len; ++i)
		if(s->str[i] == c)
			return i;

	return -1;
}

/* Bounds not checked here. Could result in undefined behavior. */
string* string_substring(string *s, int start, int len)
{
	string *sub = 0;
	int i;
	
	sub = malloc(sizeof(string));

	if(!sub)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	sub->cap = sub->len = len;
	sub->str = malloc(sizeof(char) * sub->cap);

	if(!(sub->str))
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	/* Copy contents. */
	for(i = 0; i < len; ++i)
		sub->str[i] = s->str[start + i];

	return sub;
}

string* string_free(string *s)
{
	free(s->str);
	free(s);

	return 0;
}
