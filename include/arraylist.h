#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "data.h"

typedef struct ArrayList ArrayList;
typedef struct ArrayList List;

struct ArrayList
{
    Data *arr;        
    size_t size;
    size_t capacity;
};

// A function to compare elements for equality.
typedef bool (*EqualityFunction)(const void *, const void *);
// A comparison function that defines the sorting order.
typedef int (*CompareFunction)(const void *, const void *);
// A function that returns the result of a checked conditional.
typedef bool (*CheckFunction)(const void *);

// Creates a new empty ArrayList.
ArrayList *createList(void);
// Creates a new ArrayList that is a deep copy of an existing ArrayList.
ArrayList *listClone(const ArrayList *list);

// Adds an element to the end of the ArrayList.
void listAdd(ArrayList **listPtr, void *val);
// Adds all elements from another ArrayList to the end of the current ArrayList.
void listAddAll(ArrayList **listPtr, const ArrayList *toAdd);
// Inserts an element at a specified index in the ArrayList.
void listInsert(ArrayList **listPtr, void *val, const size_t index);
// Sets the value of an element at a specified index in the ArrayList.
void listSet(ArrayList **listPr, void *val, const size_t index);
// Retains only the elements of the other ArrayList in the current ArrayList.
void listRetainAll(ArrayList **listPtr, const ArrayList *toRetain, EqualityFunction compare);
// Removes an element at a specified index from the ArrayList.
void listRemove(ArrayList **listPtr, const size_t index);
// Removes the first occurrence of a specified element from the ArrayList.
void listRemoveElement(ArrayList **listPtr, const void *toRemove, EqualityFunction compare);
// Removes elements from the ArrayList within the specified range from the start index (inclusive) to the end index (exclusive).
void listRemoveRange(ArrayList **listPtr, const size_t start, const size_t end);
// Removes all elements that satisfy the conditional.
void listRemoveIf(ArrayList **listPtr, CheckFunction check);
// Removes all occurrences of elements from another ArrayList from the current ArrayList based on a specified comparison function.
void listRemoveAll(ArrayList **listPtr, const ArrayList *toRemove, EqualityFunction compare);
// Removes all elements from the ArrayList.
void listClear(ArrayList **listPtr);
// Sorts the elements in the ArrayList using the provided comparison function.
void listSort(ArrayList **listPtr, CompareFunction compare);

// Retrieves the data stored at the specified index in the ArrayList.
void *listGet(const ArrayList *list, const size_t index);
// Returns true if the specified element exists in the ArrayList; otherwise, returns false.
bool listContains(const ArrayList *list, const void *toFind, EqualityFunction compare);
// Returns the index of the first occurrence of the specified element in the ArrayList.
int listIndexOf(const ArrayList *list, const void *toFind, EqualityFunction compare);
// Returns the index of the last occurrence of the specified element in the ArrayList.
int listLastIndexOf(const ArrayList *list, const void *toFind, EqualityFunction compare);
// Returns the current number of elements in the ArrayList.
size_t listSize(const ArrayList *list);
// Returns true if the ArrayList is empty; otherwise, returns false.
bool listIsEmpty(const ArrayList *list);

// Frees the memory associated with the ArrayList.
void freeList(ArrayList **listPtr);


void reallocList(ArrayList **listPtr, const bool isUp);

#endif