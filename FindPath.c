//-----------------------------------------------------------------------------
// FindPath.c
// Main file for Graph ADT
//-----------------------------------------------------------------------------

#include <string.h>
#include"Graph.h"

int main(int argc, char *argv[]) {
    FILE *in;
    FILE *out;

    // Check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // Opens file for reading
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    // Opens/Creates file for writing
    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    /* Input file structure:
     *
     * numVert
     * v1 v2
     * v1 v3
     * ....
     * ....
     * vn vk
     * 0  0
    */

    // Reads in number of Vertices to expect
    int numVert;
    fscanf(in, "%d", &numVert);

    // Creates Graph of size numVert
    Graph G = newGraph(numVert);
    int v;
    int u;

    // Reads incident edge list
    while (fscanf(in, "%d %d", &v, &u) == 2) {
        if (u == 0 && v == 0) break;
        addEdge(G,v,u);
    }

    // Prints out Adjacency List of Graph
    printGraph(out, G);

    // Processes each line with BFS
    int source;
    int dest;
    List L = newList();

    while (fscanf(in, "%d %d", &source, &dest)) {
        // Exit case to stop reading
        if (source == 0 && dest == 0)
            break;

        // Runs BFS
        BFS(G, source);

        // Preps getPath
        getPath(L, G, dest);

        // Stores distance
        int dist = getDist(G, dest);

        // Case Dest is unreachable
        if (dist == INF) {
            fprintf(out, "\nThe distance from %d to %d is infinity\n", source, dest);
            fprintf(out, "No %d-%d path exists\n", source, dest);
        }

            // Case Dest is reachable
        else {
            fprintf(out, "\nThe distance from %d to %d is %d\n", source, dest, dist);
            fprintf(out, "A shortest %d-%d path is: ", source, dest);
            printList(out, L);
            fprintf(out, "\n");
        }
        clear(L);
    }

    // Memory Freedom Express woo WOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
    freeGraph(&G);
    freeList(&L);
    fclose(in);
    fclose(out);
}