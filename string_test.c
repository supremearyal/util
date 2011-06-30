#include "string.h"

int main()
{
	string *s = string_init();
	string *o;
	string *subs;
	string *q = string_init_cstring("quit");
	
	string_read_line(s);
	
	while(string_cmp(s, q))
	{
		string_print(s);
		
		string_reset(s);
		string_read_line(s);
	}

	string_append(s, q);
	o = string_cat(s, q);
	string_print(s);
	string_print(o);
	string_append_cstring(o, "hello");
	string_append_char(o, 'J');
	string_print(o);
	subs = string_substring(o, 5, 6);

	printf("--\n");
	printf("%c\n", string_get(s, 5));
	printf("%d\n", string_index(o, 'o'));
	string_print(subs);
	printf("--\n");

	o = string_free(o);
	s = string_free(s);
	q = string_free(q);
	subs = string_free(subs);

	return 0;
}
