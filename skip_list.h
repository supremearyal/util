/* Copyright (c) 2010 the authors listed at the following URL, and/or
 * the authors of referenced articles or incorporated external code:
 * http://en.literateprograms.org/Skip_list_(C)?action=history&offset=20080313195128

 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:

 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * Retrieved from: http://en.literateprograms.org/Skip_list_(C)?oldid=12811
 */

#ifndef _SKIP_LIST_H
#define _SKIP_LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define MAX_LEVELS 20
#define PROB 0.5

struct _skip_node
{
	void *data;
	/* A skip node has an array of next pointers, not just one. */
	struct _skip_node **next;
};

typedef struct _skip_node skip_node;

typedef struct
{
	skip_node *head;
	/* Highest level of list. Needed for insert, delete, and
	 * search. */
	int level;
	/* Number of elements. */
	int size;
	/* Comparison function for inserting elements into list. */
	int (*compare)(const void *a, const void *b);
} skip_list;

/* Create a skip node. */
skip_node* skip_node_init(int length, void *data);
skip_list* skip_list_init(int (*compare)(const void *a, const void *b));
int skip_list_contains(skip_list *s, void *data);
void skip_list_insert(skip_list *s, void *data);
/* Returns pointer to data found to delete. If not found, return
 * NULL. */
void* skip_list_delete(skip_list *s, void *data);
/* Returns pointer to matching data. If not found, returns
 * NULL. */
void* skip_list_find(skip_list *s, void *data);
skip_list* skip_list_free(skip_list *s);

#endif
