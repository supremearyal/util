#include "string.h"

#define ASSERT(x) printf("%s\n", x ? "true" : "false")

int string_compare(string *s, string *t)
{
	printf("\"");
	string_print(s);
	printf("\"");
	printf(" == ");

	printf("\"");
	string_print(t);
	printf("\" => ");

	return string_cmp(s, t);
}

int main()
{
	string *s;
	string *t;

	s = string_init_cstring("hello");
	t = string_init_cstring("");

	ASSERT(!string_compare(s, t));

	string_reset(s);

	ASSERT(!string_compare(s, t));

	string_append_cstring(s, "helloa");
	string_append_cstring(t, "hello");

	ASSERT(!string_compare(s, t));

	s->len--;

	ASSERT(!string_compare(s, t));

	string_append_cstring(t, "hola");
	
	ASSERT(!string_compare(s, t));
	
	return 0;
}
