#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "arraylist.h"

#define INITIAL_CAPACITY 10

#define MALLOCCHECK(ptr) do\
{\
    if(ptr == NULL)\
    {\
        fprintf(stderr, "Memory allocation failed.\n");\
        free(ptr);\
        exit(1);\
    }\
} while(0)

#define CHECKSIZE(isUp) do\
{\
    if(isUp && list->size + 1 >= list->capacity)\
    {\
        reallocList(&list, true);\
    }\
    else if(!isUp && list->size < list->capacity / INITIAL_CAPACITY)\
    {\
        reallocList(&list, false);\
    }\
} while(0)

ArrayList *createList(void)
{
    ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
    Data *arr = (Data *)malloc(INITIAL_CAPACITY * sizeof(Data));
    MALLOCCHECK(list);
    MALLOCCHECK(arr);
    
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->arr = arr;

    return list;
}

ArrayList *listClone(const ArrayList *list)
{
    ArrayList *newList = createList();
    listAddAll(&newList, list);

    return newList;
}

void listAdd(ArrayList **listPtr, void *val)
{
    ArrayList *list = *listPtr;
    Data newData = createData(val);

    CHECKSIZE(true);

    list->arr[list->size++] = newData;
}

void listAddAll(ArrayList **listPtr, const ArrayList *toAdd)
{
    ArrayList *list = *listPtr;

    for(int i = 0; i < listSize(toAdd); i++)
    {
        listAdd(&list, listGet(toAdd, i));
    }
}

void listInsert(ArrayList **listPtr, void *val, const size_t index)
{
    ArrayList *list = *listPtr;

    if(index >= list->size)
    {
        listAdd(&list, val);
    }

    CHECKSIZE(true);

    Data newData = createData(val);

    Data temp0 = list->arr[index];
    list->arr[index] = newData;
    for(int i = index + 1; i < list->size + 1; i++)
    {
        Data temp1 = list->arr[i];
        list->arr[i] = temp0;
        temp0 = temp1;
    }
    list->size++;
}

void listSet(ArrayList **listPtr, void *val, const size_t index)
{
    ArrayList *list = *listPtr;

    if(index >= list->size)
    {
        return;
    }

    Data newData = createData(val);
    list->arr[index] = newData;
}

void listRetainAll(ArrayList **listPtr, const ArrayList *toRetain, EqualityFunction compare)
{
    ArrayList *list = *listPtr;

    for(int i = list->size - 1; i >= 0; i--)
    {
        if(!listContains(toRetain, listGet(list, i), compare))
        {
            listRemove(&list, i);
        }
    }
}

void listRemove(ArrayList **listPtr, const size_t index)
{
    ArrayList *list = *listPtr;

    if(index >= list->size)
    {
        return;
    }
    
    for(int i = index; i < list->size - 1; i++)
    {
        list->arr[i] = list->arr[i + 1];
    }
    list->size--;

    CHECKSIZE(false);
}

void listRemoveElement(ArrayList **listPtr, const void *toRemove, EqualityFunction compare)
{
    ArrayList *list = *listPtr;

    int index = listIndexOf(list, toRemove, compare);
    if(index == -1)
    {
        return;
    }       

    listRemove(&list, index);
}

void listRemoveRange(ArrayList **listPtr, const size_t start, const size_t end)
{
    ArrayList *list = *listPtr;

    if(start >= list->size || end > list->size)
    {
        return;
    }

    for(int i = end - 1; i >= start; i--)
    {
        listRemove(&list, i);
    }
}

void listRemoveIf(ArrayList **listPtr, CheckFunction check)
{
    ArrayList *list = *listPtr;

    for(int i = list->size - 1; i >= 0; i--)
    {
        if(check(listGet(list, i)))
        {
            listRemove(&list, i);
        }
    }
}

void listRemoveAll(ArrayList **listPtr, const ArrayList *toRemove, EqualityFunction compare)
{
    ArrayList *list = *listPtr;

    for(int i = 0; i < listSize(toRemove); i++)
    {
        while(listContains(list, listGet(toRemove, i), compare))
        {
            listRemoveElement(&list, listGet(toRemove, i), compare);
        }
    } 
}

void listClear(ArrayList **listPtr)
{
    ArrayList *list = *listPtr;

    list->size = 0;
    CHECKSIZE(false);
}

void *listGet(const ArrayList *list, const size_t index)
{
    if(index >= list->size)
    {
        return NULL;
    }

    return list->arr[index].val;    
}

bool listContains(const ArrayList *list, const void *toFind, EqualityFunction compare)
{
    for(int i = 0; i < list->size; i++)
    {
        if(compare(listGet(list, i), toFind))
        {
            return true;
        }
    }
    return false;
}

int listIndexOf(const ArrayList *list, const void *toFind, EqualityFunction compare)
{
    for(int i = 0; i < list->size; i++)
    {
        if(compare(listGet(list, i), toFind))
        {
            return i;
        }
    }
    return -1;
}

int listLastIndexOf(const ArrayList *list, const void *toFind, EqualityFunction compare)
{
    for(int i = list->size - 1; i >= 0; i--)
    {
        if(compare(listGet(list, i), toFind))
        {
            return i;
        }
    }
    return -1;
}

void swap(Data *a, Data *b)
{
    Data temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Data *arr, int low, int high, CompareFunction compare)
{
    void *pivot = arr[high].val;
    int i = low;

    for(int j = low; j < high; j++)
    {
        if(compare(arr[j].val, pivot) < 0)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);

    return i;
}

void quicksort(Data *arr, int low, int high, CompareFunction compare)
{
    if(low < high)
    {
        int pivot = partition(arr, low, high, compare);

        if(pivot > 0)
        {
            quicksort(arr, low, pivot - 1, compare);
        }
        quicksort(arr, pivot + 1, high, compare);
    }
}

void listSort(ArrayList **listPtr, CompareFunction compare)
{
    ArrayList *list = *listPtr;

    quicksort(list->arr, 0, list->size - 1, compare);
}

size_t listSize(const ArrayList *list)
{
    return list->size;
}

bool listIsEmpty(const ArrayList *list)
{
    return (list->size == 0) ? true : false;
}

void freeList(ArrayList **listPtr)
{
    ArrayList *list = *listPtr;
    free(list->arr);
    free(list);
}

void reallocList(ArrayList **listPtr, const bool isUp)
{
    ArrayList *list = *listPtr;
    if(list->size == 0)
    {
        if(list->capacity == INITIAL_CAPACITY)
            return;
        
        list->capacity = INITIAL_CAPACITY;
        list->arr = (Data *)realloc(list->arr, list->capacity * sizeof(Data));
        return;
    }

    if(isUp)
    {
        list->arr = (Data *)realloc(list->arr, list->capacity * INITIAL_CAPACITY * sizeof(Data));
        list->capacity *= INITIAL_CAPACITY;
    }
    else
    {
        list->arr = (Data *)realloc(list->arr, list->capacity / INITIAL_CAPACITY * sizeof(Data));
        list->capacity /= INITIAL_CAPACITY;
    }
    MALLOCCHECK(list);
}