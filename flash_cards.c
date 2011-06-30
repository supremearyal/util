#include "string.h"
#include "pair.h"
#include "vector.h"
#include "map.h"

#include <time.h>
#include <stdio.h>

int card_cmp_map(const void *a, const void *b)
{
	return string_cmp(((pair *) a)->first, ((pair *) b)->first);
}

int card_cmp_vec(const void *a, const void *b)
{
	return string_cmp(* (string **) a, * (string **) b);
}

void read_file(FILE *f, map *m, string *quit)
{
	string *front;
	string *back;

	front = string_init();
	string_read_line_stream(f, front);
	
	while(string_cmp(front, quit))
	{
		back = string_init();
		string_read_line_stream(f, back);
		map_add(m, front, back);

		front = string_init();
		string_read_line_stream(f, front);
	}

	string_free(front);
}

void list_map(map *m)
{
	map_iterator *i;
	pair *d;
	
	/* Iterate the map. */
	for(i = map_begin(m); i; i = map_next(i))
	{
		d = i->data;
		string_print(d->first);
		printf(" => ");
		string_println(d->second);
	}
}

void ask_user(map *m, string *q)
{
	vector *k;
	string *answer;
	string *question;
	string *tmp;
	int i; /* Iterate vector. */
	int c; /* Return value from string read. */

	k = vector_init(card_cmp_vec);
	i = 0;
	/* Generate permutation. */
	map_keys(m, k);
	vector_shuffle(k);
	answer = string_init();

	/* Can only get a question if there are questions. */
	if(vector_length(k) <= 0)
		goto done;
	
	question = vector_get(k, i++);
	
	string_print(question);
	printf(" => ");
	c = string_read_line(answer);
	
	while(string_cmp(answer, q))
	{
		/* If the user input ^D, handle that. */
		if(c == EOF)
			putchar('\n');

		tmp = map_get(m, question);

		/* If answer is wrong, print correct answer. */
		if(!tmp || string_cmp(tmp, answer))
		{
			string_print(question);
			printf(" := ");
			string_println(map_get(m, question));
		}

		if(i >= k->len)
		{
			vector_shuffle(k);
			i = 0;
		}
		question = vector_get(k, i++);
		
		string_print(question);
		printf(" => ");
		string_reset(answer);
		c = string_read_line(answer);
	}

done:
	vector_free(k);
	string_free(answer);
}

int main(int argc, char **argv)
{
	FILE *f;
	map *cards;
	map_iterator *i;
	pair *d;
	string *quit;

	f = 0;
	cards = map_init(card_cmp_map);
	quit = string_init_cstring("");

	if(argc > 1)
	{
		f = fopen(argv[1], "r");

		if(!f)
		{
			fprintf(stderr, "Cannot open file: %s\n", argv[1]);
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(1);
	}

	read_file(f, cards, quit);
	/*list_map(cards);*/
	/* Change the quit text (the API is a little bad here). I am
	 * resetting and appending here. */
	string_reset(quit);
	string_append_cstring(quit, "quit");
	ask_user(cards, quit);

	for(i = map_begin(cards); i; i = map_next(i))
	{
		d = i->data;
		string_free(d->first);
		string_free(d->second);
	}

	fclose(f);
	string_free(quit);
	map_free(cards);

	return 0;
}
