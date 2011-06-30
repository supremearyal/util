#ifndef _STRING_H
#define _STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_STRING_CAPACITY 10

extern size_t strlen(const char *s);
extern void* memcpy(void *dest, const void *src, size_t n);

typedef struct
{
	char *str;
	int cap;
	int len;
} string;

string* string_init();
string* string_init_cstring(char *c);
void string_shrink(string *s);
void string_grow(string *s);
/* Makes internal length 0 so we can use given string again without
 * allocating more memory. */
void string_reset(string *s);
int string_length(string *s);
/* Returns a cstring for this string. Makes a new copy. */
char* string_to_cstring(string *s);
int string_read_line(string *s);
int string_read_line_stream(FILE *f, string *s);
void string_print(string *s);
void string_println(string *s);
int string_cmp(string *a, string *b);

string* string_cat(string *a, string *b);
string* string_cpy(string *s);
void string_append(string *s, string *o);
void string_append_cstring(string *s, char *c);
void string_append_char(string *s, char c);
char string_get(string *s, int i);
int string_index(string *s, char c);

string* string_substring(string *s, int start, int len);

/* Not yet implemented below this line. */
/* Boyer moore search. */
/* Splitting by some character. Use yet not built vecotr .*/
/* Not yet implemented above this line. */

/* Returns NULL so we can do s = string_free(s). */
string* string_free(string *s);

#endif
