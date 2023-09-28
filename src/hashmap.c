#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "arraylist.h"
#include "pair.h"
#include "hashmap.h"

#define HASHCONSTANT 0.6180339887

#define MALLOCCHECK(ptr) do\
{\
    if(ptr == NULL)\
    {\
        fprintf(stderr, "Memory allocation failed.\n");\
        free(ptr);\
        exit(1);\
    }\
} while(0)

HashMap *createMap(const size_t size, ConvertFunction convert, EqualityFunction comparePairKeys)
{
    HashMap *newMap = (HashMap *)malloc(sizeof(HashMap));
    MALLOCCHECK(newMap);

    ArrayList *buckets = createList();
    newMap->size = size;
    for(int i = 0; i < newMap->size; i++)
    {
        ArrayList *bucket = createList();
        listAdd(&buckets, bucket);
    }
    newMap->buckets = buckets;
    newMap->convert = convert;
    newMap->comparePairKeys = comparePairKeys;

    return newMap;
}

double floorValue(double val)
{
    if(val >= 0.0)
    {
        return (double)((long)val);
    } else
    {
        double intPart = (double)((long)val);
        return (intPart == val) ? intPart : intPart - 1.0;
    }
}

double frac(double val)
{
    return val - floorValue(val);
}

size_t hash(const HashMap *map, const void *key, ConvertFunction convert)
{
    double hashCode = floorValue(map->size * frac(convert(key) * HASHCONSTANT));

    return (size_t)hashCode;
}

void mapPut(HashMap **mapPtr, void *key, void *value)
{ 
    HashMap *map = *mapPtr;
    size_t hashCode = hash(map, key, map->convert);

    ArrayList *bucket = listGet(map->buckets, hashCode);
    Pair *newPair = createPair(key, value); 
    int index = listIndexOf(bucket, newPair, map->comparePairKeys);
    if(index != -1)
    {
        listSet(&bucket, newPair, listIndexOf(bucket, newPair, map->comparePairKeys));
    } 
    else
    {
        listAdd(&bucket, newPair);
    }
}

void *mapGet(const HashMap *map, void *key)
{
    size_t hashCode = hash(map, key, map->convert);

    ArrayList *bucket = listGet(map->buckets, hashCode);
    Pair *toFind = createPair(key, NULL);
    int index = listIndexOf(bucket, toFind, map->comparePairKeys);
    if(index != -1)
    {
        Pair *toReturn = (Pair *)listGet(bucket, index);
        return toReturn->value; 
    }

    return NULL;
}

void mapRemove(HashMap **mapPtr, void *key)
{
    HashMap *map = *mapPtr;
    size_t hashCode = hash(map, key, map->convert);

    ArrayList *bucket = listGet(map->buckets, hashCode);
    Pair *toFind = createPair(key, NULL); 
    int index = listIndexOf(bucket, toFind, map->comparePairKeys);
    if(index != -1)
    {
        listRemove(&bucket, index);
    }
}

void freeMap(HashMap **mapPtr)
{
    HashMap *map = *mapPtr;

    for(int i = 0; i < listSize(map->buckets); i++)
    {
        ArrayList *toFree = listGet(map->buckets, i);
        freeList(&toFree);
    }
    freeList(&(map->buckets));
    free(map);
}