//-----------------------------------------------------------------------------
// GraphTest.c
// Test file for Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    // Creates Graph G and populates it
    Graph G = newGraph(6);
    addEdge(G, 1, 3);
    addEdge(G, 1, 5);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 3, 4);

    // Prints basic Graph Structure
    printf("Star Graph:\n");
    printGraph(stdout, G);
    printf("\n");

    // Tests BFS
    printf("Running BFS with source = 1\n");
    BFS(G, 1);
    printf("\n");

    // Tests misc. Functions
    printf("Testing basic properties of Graph\n");
    printf("Source should be 1 -> %d\n", getSource(G));
    printf("Order of Graph should be 6 -> %d\n", getOrder(G));
    printf("Size of Graph should be 5 -> %d\n", getSize(G));
    printf("\n");

    // Testing Parenting
    printf("Testing Parenting\n");
    printf("Parent of S should be 0 -> %d\n", getParent(G, getSource(G)));
    printf("Parent of 6 should be 0 -> %d\n", getParent(G, 6));
    printf("Parent of 5 should be 1 -> %d\n", getParent(G, 5));
    printf("Parent of 4 should be 3 -> %d\n", getParent(G, 4));
    printf("Parent of 3 should be 1 -> %d\n", getParent(G, 3));
    printf("\n");

    // Tests getPath
    printf("Testing getPath from 1 to 4\n");
    List L = newList();
    getPath(L, G, 4);
    printf("Path should be 1 3 4 -> ");
    printList(stdout, L);
    printf("\n\n");

    // Additional getPath
    printf("Testing getPath from 1 to 2 w/o clearing List L\n");
    getPath(L, G, 2);
    printf("Path should be 1 3 4 1 5 2 -> ");
    printList(stdout, L);
    printf("\n\n");

    // Clears List
    printf("Clearing List\n");
    clear(L);
    printf("List is cleared -> ");
    printList(stdout, L);
    printf("\n\n");

    // Nullifying Graph
    printf("Nullifying Graph\n");
    makeNull(G);
    printGraph(stdout, G);
    printf("\n");

    // Testing Null Graph Properties
    printf("Testing basic properties again\n");
    printf("Source should be 0 -> %d\n", getSource(G));
    printf("Order of Graph should be 6 -> %d\n", getOrder(G));
    printf("Size of Graph should be 0 -> %d\n", getSize(G));
    printf("\n");

    // Frees Memory
    freeGraph(&G);
    freeList(&L);

    return 0;
}