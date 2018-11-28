//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj {
    List *adjList;

    int *distance;
    int *parent;
    int *color;

    int order;
    int size;
    int source;
} GraphObj;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns a Graph pointing to a newly created GraphObj with n vertices.
Graph newGraph(int n) {
    int numTerms = n + 1;

    Graph G = malloc(sizeof(GraphObj));

    G->adjList = malloc(sizeof(List) * (numTerms));
    G->distance = malloc(sizeof(int) * (numTerms));
    G->parent = malloc(sizeof(int) * (numTerms));
    G->color = malloc(sizeof(int) * (numTerms));

    G->order = n;
    G->size = 0;
    G->source = NIL;

    for (int i = 0; i < numTerms; i++) {
        G->adjList[i] = newList();
        G->distance[i] = INF;
        G->parent[i] = NIL;
        G->color[i] = WHITE;
    }

    return (G);
}

// freeGraph()
// Frees all dynamic memory associated with the Graph *pG, then sets the handle
// *pG to NULL.
void freeGraph(Graph *pG) {
    if (pG == NULL) {
        printf("Graph Error: freeGraph() called on NULL Graph reference\n");
        exit(1);
    }

    for (int i = 0; i < getOrder(*pG) + 1; i++)
        freeList(&(*pG)->adjList[i]);

    free((*pG)->adjList);
    free((*pG)->distance);
    free((*pG)->parent);
    free((*pG)->color);

    free(*pG);
    *pG = NULL;
}


// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of Graph G.
int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph Error: getOrder() called on NULL Graph reference\n");
        exit(1);
    }
    return G->order;
}

// getSize()
// Returns the size of the graph G.
int getSize(Graph G) {
    if (G == NULL) {
        printf("Graph Error: getSize() called on NULL Graph reference\n");
        exit(1);
    }
    return G->size;
}

// getSource()
// Returns the source vertex most recently used in function BFS() otherwise NIL.
int getSource(Graph G) {
    if (G == NULL) {
        printf("Graph Error: getSource() called on NULL Graph reference\n");
        exit(1);
    }
    return G->source;
}

// getParent()
// Returns the parent of vertex u in BFS Tree.
// Precondition: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: getParent() called on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: getParent() called on vertex outside range of Graph\n");
        exit(1);
    }
    return G->parent[u];
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF
// if BFS() has not been called yet.
// Precondition: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if (G == NULL) {
        printf("Graph Error: getDist() called on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: getDist() called on vertex outside range of Graph\n");
        exit(1);
    }

    if (getSource(G) == NIL)
        return INF;
    else
        return G->distance[u];
}

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u
// or appends to L the value NIL if no such path exists.
// BFS() must have been called prior on G
// Precondition: 1 <= u <= getOrder(G), getSource(G) != NIL
void getPath(List L, Graph G, int u) {
    if (L == NULL) {
        printf("Graph Error: getPath() called on NULL List reference\n");
        exit(1);
    }
    if (G == NULL) {
        printf("Graph Error: getPath() called on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: getPath() called on vertex outside range of Graph\n");
        exit(1);
    }
    if (getSource(G) == NIL) {
        printf("Graph Error: getPath() called on NIL Source\n");
        exit(1);
    }

    // Base Case: Reaches Source
    if (u == G->source)
        append(L, u);

        // Break Case: Vertex is unreachable from source
    else if (G->parent[u] == NIL)
        append(L, NIL);

        // Climbs back up towards source
    else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }


    // Iterative solution to getPath()
    // TODO: THIS IS INCORRECT WHEN LIST IS NOT CLEARED
    /*if (G->parent[u] == NIL)
	prepend(L, NIL);

    else {
	int x = u;

	// Prepends all but S to list
	while (x != G->source) {
	    prepend(L, x);
	    x = G->parent[x];
	}
	// Prepends S to list
	prepend(L, x);
    }*/
}


// Manipulation procedures ----------------------------------------------------

// makeNull()
// Deletes all edges of G, restoring it to its original no edge state.
void makeNull(Graph G) {
    if (G == NULL) {
        printf("Graph Error: makeNull() called on NULL Graph reference\n");
        exit(1);
    }

    for (int i = 1; i < getOrder(G) + 1; i++) {
        clear(G->adjList[i]);
        G->distance[i] = INF;
        G->parent[i] = NIL;
        G->color[i] = WHITE;
    }
    G->source = NIL;
    G->size = 0;

    // Leaves Order intact because Graph is just broken into components now
}

// addEdge()
// Inserts a new edge joining u to v.
// Precondition: 1 <= u, v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: addEdge() called on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: addEdge() called on vertex u outside range of Graph\n");
        exit(1);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Graph Error: addEdge() called on vertex v outside range of Graph\n");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);

    // Decrements because addArc() increments each time but this
    // should only be 1 edge in size
    G->size--;
}

// addArc()
// Inserts a new directed edge from u to v.
// Precondition: 1 <= u, v <= getOrder(G)
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: addArc() called on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: addArc() called on vertex u outside range of Graph\n");
        exit(1);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Graph Error: addArc() called on vertex v outside range of Graph\n");
        exit(1);
    }

    // Moves iterator
    moveFront(G->adjList[u]);
    // While iterator is inbounds and has not reached/passed v yet
    while (index1(G->adjList[u]) > -1 && v > get(G->adjList[u]))
        moveNext(G->adjList[u]);

    // Adds to the end because falls off the back
    if (index1(G->adjList[u]) == -1)
        append(G->adjList[u], v);
        // Inserts before because cursor is currently on value greater than u
    else
        insertBefore(G->adjList[u], v);

    G->size++;
}

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting color,
// distance, parent and source fields of G accordingly.
void BFS(Graph G, int s) {
    if (G == NULL) {
        printf("Graph Error: BFS() called on NULL Graph reference\n");
        exit(1);
    }

    // Reference Vertices
    int u;
    int v;

    // Sets BFS Source
    G->source = s;

    // Initializes all values to default conditions
    for (int i = 1; i < getOrder(G) + 1; i++) {
        G->distance[i] = INF;
        G->parent[i] = NIL;
        G->color[i] = WHITE;
    }

    // Initializes Source
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;

    // Creates Queue of Vertices to iterate through starting with source
    List Queue = newList();
    append(Queue, s);

    // While there are Vertices in the Queue, keep iterating
    while (length(Queue) != 0) {
        // Fetches and removes next value in Queue
        u = front(Queue);
        deleteFront(Queue);

        // Focuses cursor on u's adjacency list
        moveFront(G->adjList[u]);

        // Iterates through u's adj list
        while (index1(G->adjList[u]) != -1) {
            v = get(G->adjList[u]);

            // If not yet visited
            if (G->color[v] == WHITE) {
                G->distance[v] = G->distance[u] + 1;
                G->parent[v] = u;
                G->color[v] = GRAY;
                append(Queue, v);
            }
            // Iterates to next adjacent vertex or -1 if none remaining
            moveNext(G->adjList[u]);
        }
        // Done processing value from Queue, so color Black
        G->color[u] = BLACK;
    }

    // Memory Leak Patrol toot tooooooot
    freeList(&Queue);
    Queue = NULL;
}


// Other Functions ------------------------------------------------------------

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE *out, Graph G) {
    if (out == NULL) {
        printf("Graph Error: printGraph() called on NULL FILE reference\n");
        exit(1);
    }
    if (G == NULL) {
        printf("Graph Error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }

    // Iterates through and writes Graph out
    for (int i = 1; i < getOrder(G) + 1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjList[i]);
        fprintf(out, "\n");
    }
}