#ifndef HASHMAP_H
#define HASHMAP_H

#include "arraylist.h"
#include "pair.h"

typedef struct HashMap HashMap;

typedef long (*ConvertFunction)(const void *key);

struct HashMap
{
    ArrayList *buckets;
    size_t size;
    ConvertFunction convert;
    EqualityFunction comparePairKeys;
};

HashMap *createMap(const size_t size, ConvertFunction convert, EqualityFunction comparePairKeys);

void mapPut(HashMap **mapPtr, void *key, void *value);
void *mapGet(const HashMap *map, void *key);
void mapRemove(HashMap **mapPtr, void *key);

bool mapContains(const HashMap *map, void *key);

void freeMap(HashMap **mapPtr);

#endif