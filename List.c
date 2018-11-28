//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
    int data;
    struct NodeObj *next;
    struct NodeObj *prev;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int cIndex;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to new empty List object.
List newList(void) {
    List L;
    L = malloc(sizeof(struct ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->cIndex = -1;
    return (L);
}

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.S
void freeList(struct ListObj **pL) {
    if (pL == NULL || *pL == NULL) {
        printf("List Error: freeList() called on NULL List reference\n");
        exit(1);
    }

    clear(*pL);
    free(*pL);
    *pL = NULL;
}


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L) {
    if (L == NULL) {
        printf("List Error: length() called on NULL List reference\n");
        exit(1);
    }
    return (L->length);
}

// index1()
// Returns the index1 of cursor or -1 if undefined
int index1(List L) {
    if (L == NULL) {
        printf("List Error: index1() called on NULL List reference\n");
        exit(1);
    }
    if (L->cursor == NULL) {
        return -1;
    }
    return L->cIndex;
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L) {
    if (L == NULL) {
        printf("List Error: front() called on NULL List reference\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: front() called on an empty List\n");
        exit(1);
    }
    return (L->front->data);
}

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L) {
    if (L == NULL) {
        printf("List Error: back() called on NULL List reference\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: back() called on empty List\n");
        exit(1);
    }
    return (L->back->data);
}

// get()
// returns the cursor element
// Pre: !isEmpty(L) & index1(L)>=0
int get(List L) {
    if (L == NULL) {
        printf("List Error: get() called on NULL List reference\n");
        exit(1);
    } else if (isEmpty(L)) {
        printf("List Error: get() called on empty List\n");
        exit(1);
    } else if (L->cIndex < 0) {
        printf("List Error: get() called on undefined cursor\n");
        exit(1);
    }
    return L->cursor->data;
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B) {
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    if (A == NULL || B == NULL) {
        printf("List Error: equals() called on NULL List reference\n");
        exit(1);
    }

    eq = (A->length == B->length);
    N = A->front;
    M = B->front;
    while (eq && N != NULL) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// isEmpty()
// Returns true (1) if Lqwq is empty, otherwise returns false (0)
int isEmpty(List L) {
    if (L == NULL) {
        printf("List Error: isEmpty() called on NULL List reference\n");
        exit(1);
    }
    return (L->length == 0);
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets the list to original empty state.
void clear(List L) {
    while (!isEmpty(L))
        deleteFront(L);
}

// moveFront()
// Moves the cursor to point to front element if non-empty, otherwise nothing
void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: moveFront() called on NULL List reference\n");
        exit(1);
    }

    if (!isEmpty(L)) {
        L->cursor = L->front;
        L->cIndex = 0;
    }
}

// moveBack()
// Moves the cursor to point to back element if non-empty, otherwise nothing
void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: moveBack() called on NULL List reference\n");
        exit(1);
    }

    if (!isEmpty(L)) {
        L->cursor = L->back;
        L->cIndex = L->length - 1;
    }
}

// movePrev()
// If cursor is defined and not at front, move cursor towards front, otherwise
// undefined.
void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: movePrev() called on NULL List reference\n");
        exit(1);
    }

    if (L->cursor == NULL) {
    } else if (L->cIndex == 0) {
        L->cursor = NULL;
        L->cIndex = -1;
    } else {
        L->cursor = L->cursor->prev;
        L->cIndex--;
    }
}

// moveNext()
// If cursor is defined and not at back, move cursor towards back, otherwise
// undefined
void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: moveNext() called on NULL List reference\n");
        exit(1);
    }

    if (L->cursor == NULL) {
    } else if (L->cIndex == (L->length - 1)) {
        L->cursor = NULL;
        L->cIndex = -1;
    } else {
        L->cursor = L->cursor->next;
        L->cIndex++;
    }
}

// prepend()
// Insert the element at the front of List
void prepend(List L, int data) {
    if (L == NULL) {
        printf("List Error: prepend() called on NULL List reference\n");
        exit(1);
    }

    Node N = newNode(data);

    if (isEmpty(L)) {
        L->front = N;
        L->back = N;
    } else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;

        if (L->cIndex > -1) {
            L->cIndex++;
        }
    }
    L->length++;
}

// append()
// Insert the element at the back of List
void append(List L, int data) {
    if (L == NULL) {
        printf("List Error: append() called on NULL List reference\n");
        exit(1);
    }

    Node N = newNode(data);

    if (isEmpty(L)) {
        L->front = N;
        L->back = N;
    } else {
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

// insertBefore()
// Insert the element before the cursor
// Pre: !isEmpty(L) & index1(L)>=0
void insertBefore(List L, int data) {
    if (L == NULL) {
        printf("List Error: insertBefore() called on NULL List reference\n");
        exit(1);
    } else if (isEmpty(L)) {
        printf("List Error: insertBefore() called on an empty List\n");
        exit(1);
    } else if (index1(L) < 0) {
        printf("List Error: insertBefore() called on undefined cursor\n");
        exit(1);
    }

    Node N = newNode(data);
    Node n1 = L->cursor->prev;

    if (n1 == NULL) {
        N->prev = NULL;
        L->front = N;
    } else {
        N->prev = n1;
        n1->next = N;
    }

    N->next = L->cursor;
    L->cursor->prev = N;

    L->length++;
    L->cIndex++;
}

// insertAfter()
// Insert the element after the cursor
// Pre: !isEmpty(L) & index1(L)>=0
void insertAfter(List L, int data) {
    if (L == NULL) {
        printf("List Error: insertAfter() called on NULL List reference\n");
        exit(1);
    } else if (isEmpty(L)) {
        printf("List Error: insertAfter() called on an empty List\n");
        exit(1);
    } else if (index1(L) < 0) {
        printf("List Error: insertAfter() called on undefined cursor\n");
        exit(1);
    }

    Node N = newNode(data);
    Node n1 = L->cursor->next;

    if (n1 == NULL) {
        N->next = NULL;
        L->back = N;
    } else {
        N->next = n1;
        n1->prev = N;
    }

    N->prev = L->cursor;
    L->cursor->next = N;

    L->length++;
}

// deleteFront()
// Deletes the front element.
// Pre: !isEmpty(L)
void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: deleteFront() called on NULL List reference\n");
        exit(1);
    } else if (isEmpty(L)) {
        printf("List Error: deleteFront() called on an empty List\n");
        exit(1);
    }

    Node n0 = L->front;
    Node n1 = n0->next;

    if (n1 != NULL) {
        L->front = n1;
        L->front->prev = NULL;
    } else {
        L->front = NULL;
        L->back = NULL;
    }

    if (L->cIndex > -1) {
        L->cIndex--;
        if (L->cIndex < 0) {
            L->cursor = NULL;
        }
    }

    freeNode(&n0);
    L->length--;
}

// deleteBack()
// Deletes the back element.
// Pre: !isEmpty(L)
void deleteBack(List L) {
    if (L == NULL) {
        printf("List Error: deleteBack() called on NULL List reference\n");
        exit(1);
    } else if (isEmpty(L)) {
        printf("List Error: deleteBack() called on an empty List\n");
        exit(1);
    }

    Node n0 = L->back;
    Node n1 = n0->prev;


    if (n1 != NULL) {
        L->back = n1;
        L->back->next = NULL;
    } else {
        L->front = NULL;
        L->back = NULL;
    }

    if (L->cIndex == (L->length - 1)) {
        L->cIndex = -1;
        L->cursor = NULL;
    }

    freeNode(&n0);
    L->length--;
}

// delete()
// Deletes the back element.
// Pre: !isEmpty(L) & index1(L)>-1
void delete(List L) {
    if (L == NULL) {
        printf("List Error: delete() called on NULL List reference\n");
        exit(1);
    } else if (isEmpty(L)) {
        printf("List Error: delete() called on an empty List\n");
        exit(1);
    } else if (index1(L) < 0) {
        printf("List Error: delete() called on undefined cursor\n");
        exit(1);
    }

    Node n0 = L->cursor;
    Node n1 = n0->prev;
    Node n2 = n0->next;

    // If front, back, single element, else
    if (n1 == NULL && n2 != NULL) {
        deleteFront(L);
    } else if (n2 == NULL && n1 != NULL) {
        deleteBack(L);
    } else if (n1 == NULL) {
        deleteFront(L);
    } else {
        n1->next = n2;
        n2->prev = n1;
        freeNode(&n0);
        L->length--;
    }

    L->cIndex = -1;
    L->cursor = NULL;
}


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
// Pre: Assumes FILE *out is open already
void printList(FILE *out, struct ListObj *L) {
    if (L == NULL) {
        printf("List Error: printList() called on NULL List reference\n");
        exit(1);
    } else if (out == NULL) {
        printf("List Error: printList() unable to open file for writing\n");
        exit(1);
    }

    Node N = NULL;

    for (N = L->front; N != NULL; N = N->next) {
        fprintf(out, "%d ", N->data);
    }
}

// copyList()
// Returns a copy of the specified List
List copyList(List L) {

    if (L == NULL) {
        printf("List Error: copyList() called on NULL List reference\n");
        exit(1);
    }

    List nL = newList();
    Node N = L->front;

    while (N != NULL) {
        append(nL, N->data);
        N = N->next;
    }

    return nL;
}

