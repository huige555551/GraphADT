//-----------------------------------------------------------------------------
// Graph.h
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#ifndef GRAPHADT_GRAPH_H
#define GRAPHADT_GRAPH_H

#include"List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define INF -1
#define NIL 0

// Exported type --------------------------------------------------------------
typedef struct GraphObj *Graph;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns a Graph pointing to a newly created GraphObj with n vertices.
Graph newGraph(int n);

// freeGraph()
// Frees all dynamic memory associated with the Graph *pG, then sets the handle
// *pG to NULL.
void freeGraph(Graph *pG);


// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of Graph G.
int getOrder(Graph G);

// getSize()
// Returns the size of the graph G.
int getSize(Graph G);

// getSource()
// Returns the source vertex most recently used in function BFS() otherwise NIL.
int getSource(Graph G);

// getParent()
// Returns the parent of vertex u in BFS Tree.
// Precondition: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF
// if BFS() has not been called yet.
// Precondition: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u
// or appends to L the value NIL if no such path exists.
// Precondition: 1 <= u <= getOrder(G), getSource(G) != NIL
void getPath(List L, Graph G, int u);


// Manipulation procedures ----------------------------------------------------

// makeNull()
// Deletes all edges of G, restoring it to its original no edge state.
void makeNull(Graph G);

// addEdge()
// Inserts a new edge joining u to v.
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v.
void addArc(Graph G, int u, int v);

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting color,
// distance, parent and source fields of G accordingly.
void BFS(Graph G, int s);


// Other Functions ------------------------------------------------------------

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE *out, Graph G);


#endif //GRAPHADT_GRAPH_H
