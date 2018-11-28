//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

#include<stdio.h>
#include<stdlib.h>

// Exported type --------------------------------------------------------------
typedef struct ListObj *List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL);


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L);

// index1()
// Returns the index1 of Cursor.
int index1(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
int front(List L);

// back()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
int back(List L);

// get()
// Returns the value the cursor is pointing to
int get(List L);

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets list to empty state
void clear(List L);

// moveFront()
// Moves cursor to the front
void moveFront(List L);

// moveBack()
// Moves cursor to the back
void moveBack(List L);

// movePrev()
// Moves cursor back one index1
void movePrev(List L);

// moveNext()
// Moves cursor forward one index1
void moveNext(List L);

// prepend()
// Inserts data at the back of list
void prepend(List L, int data);

// append()
// Inserts data at the front of list
void append(List L, int data);

// insertBefore()
// Inserts data before cursor
void insertBefore(List L, int data);

// insertAfter()
// Inserts data after cursor
void insertAfter(List L, int data);

// deleteFront()
// Deletes the front element
void deleteFront(List L);

// deleteBack()
// Deletes the back element
void deleteBack(List L);

// delete()
// Deletes the element cursor is pointing to
void delete(List L);


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE *out, List L);

// copyList
// Returns a copy of this list
List copyList(List L);

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);

#endif