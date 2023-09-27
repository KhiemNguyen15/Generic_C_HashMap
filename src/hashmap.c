#include <stdio.h>
#include <stdlib.h>

#include "arraylist.h"
#include "hashmap.h"

#define MALLOCCHECK(ptr) do\
{\
    if(ptr == NULL)\
    {\
        fprintf(stderr, "Memory allocation failed.\n");\
        free(ptr);\
        exit(1);\
    }\
} while(0)

HashMap *createMap(const size_t size, HashFunction hash)
{
    HashMap *newMap = (HashMap *)malloc(sizeof(HashMap));
    MALLOCCHECK(newMap);

    ArrayList *buckets = createList();
    for(int i = 0; i < size; i++)
    {
        ArrayList *bucket = createList();
        listAdd(&buckets, bucket);
    }
    newMap->buckets = buckets;

    if(hash != NULL)
    {
        newMap->hash = hash;
    }
}

/* Hash functon notes

Division method: if n is table size, then h(k) = k % n (say k = 7)
Multiplication method: floor(m * frac(c * key))
Where floor(x) = int part of real number x

c = 0.6180339887
or 0.3819660113
h(1011), m = 997 (table size)
= 454

frac(x) = x - floor(x)
floor(997 * frac(1101 * .61....)) result is 0 <= result < m

**The Method:** h(x) = floor(m * frac(c * x))

*/