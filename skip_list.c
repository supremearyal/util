#include "skip_list.h"

/* Random number between 0 and 1. */
float frand()
{
	return (float) rand() / RAND_MAX;
}

/* Random number function for generating nodes. */
int rand_node_level()
{
	static int seeded = 0;
	int level = 0;

	if(!seeded)
	{
		/*srand((unsigned) time(NULL));*/
		seeded = 1;
	}

	while(frand() < PROB && level < MAX_LEVELS)
		++level;

	return level;
}

skip_node* skip_node_init(int level, void *data)
{
	skip_node *s = malloc(sizeof(skip_node));

	if(!s)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	s->next = calloc(level + 1, sizeof(skip_node *));

	if(!(s->next))
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	s->data = data;

	return s;
}

skip_list* skip_list_init(int (*compare)(const void *a, const void *b))
{
	skip_list *s = malloc(sizeof(skip_list));

	if(!s)
	{
		fprintf(stderr, "Insufficient memory.\n");
		exit(EXIT_FAILURE);
	}

	s->head = skip_node_init(MAX_LEVELS, 0);
	s->level = 0;
	s->size = 0;
	s->compare = compare;

	return s;
}

int skip_list_contains(skip_list *s, void *data)
{
	int i;
	skip_node *j;

	j = s->head;

	for(i = s->level; i >= 0; --i)
		while(j->next[i] && s->compare(j->next[i]->data, data) < 0)
			j = j->next[i];

	j = j->next[0];

	if(j && !(s->compare(j->data, data)))
		return 1;

	return 0;
}

/* Ignore duplicate entries. */
void skip_list_insert(skip_list *s, void *data)
{
	int i;
	skip_node *j;
	skip_node *update[MAX_LEVELS + 1];
	int level;

	j = s->head;
	memset(update, 0, MAX_LEVELS + 1);

	for(i = s->level; i >= 0; --i)
	{
		while(j->next[i] && s->compare(j->next[i]->data, data) < 0)
			j = j->next[i];
		update[i] = j;
	}

	j = j->next[0];

	if(!j || s->compare(j->data, data))
	{
		level = rand_node_level();

		if(level > s->level)
		{
			for(i = s->level + 1; i <= level; ++i)
				update[i] = s->head;
			s->level = level;
		}

		j = skip_node_init(level, data);
		s->size++;

		for(i = 0; i <= level; ++i)
		{
			j->next[i] = update[i]->next[i];
			update[i]->next[i] = j;
		}
	}
}

void* skip_list_delete(skip_list *s, void *data)
{
	int i;
	skip_node *j;
	skip_node *update[MAX_LEVELS + 1];
	void *found;

	j = s->head;
	memset(update, 0, MAX_LEVELS + 1);
	found = 0;

	for(i = s->level; i >= 0; --i)
	{
		while(j->next[i] && s->compare(j->next[i]->data, data) < 0)
			j = j->next[i];
		update[i] = j;
	}

	j = j->next[0];

	if(j && !(s->compare(j->data, data)))
	{
		s->size--;
		/* Found pointer to data. */
		found = j->data;
		
		for(i = 0; i <= s->level; ++i)
		{
			if(update[i]->next[i] != j)
				break;
			update[i]->next[i] = j->next[i];
		}

		free(j->next);
		free(j);
		while(s->level > 0 && !(s->head->next[s->level]))
			--s->level;
	}

	return found;
}

void* skip_list_find(skip_list *s, void *data)
{
	int i;
	skip_node *j;
	void *found;

	j = s->head;
	found = 0;

	for(i = s->level; i >= 0; --i)
	{
		while(j->next[i] && s->compare(j->next[i]->data, data) < 0)
			j = j->next[i];
	}

	j = j->next[0];

	/* Check if j is NULL. */
	if(j && !(s->compare(j->data, data)))
	{
		/* Found pointer to data. */
		found = j->data;
	}

	return found;
}

/* Caller frees constituent data. */
skip_list* skip_list_free(skip_list *s)
{
	skip_node *i;
	skip_node *t;

	i = s->head->next[0];

	while(i)
	{
		t = i;
		i = i->next[0];
		free(t->next);
		free(t);
	}

	free(s->head->next);
	free(s->head);
	free(s);

	return 0;
}
