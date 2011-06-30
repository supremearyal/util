#ifndef _GRAPH_H
#define _GRAPH_H

#include "llist.h"
#include "skip_list.h"
#include "map.h"

/* Defines a undirected graph. */

typedef struct
{
	/* Adjacency list representation of graph. */
	map *adj;
	int (*compare)(const void *a, const void *b);
} graph;

typedef skip_node graph_iterator;

/* Access the graph in some order (the order of the hashmap composing
 * the graph) since it encapsulates the graph. */
graph_iterator* graph_begin(graph *g);
graph_iterator* graph_next(graph_iterator *i);
/* Initialize graph. Caller responsible for freeing data in the
 * graph. */
graph* graph_init(int (*compare)(const void *a, const void *b));
/* Add a node to the graph (if it doesn't exist) . */
graph* graph_add(graph *g, void *data);
/* Connect two nodes (if they exist). */
void graph_connect(graph *g, void *a, void *b);
/* Remove edge between nodes. */
void graph_disconnect(graph *g, void *a, void *b);
/* Remove a node from a graph. */
graph* graph_remove(graph *g, void *data);
graph* graph_free(graph *g);

#endif
