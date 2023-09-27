#ifndef HASHMAP_H
#define HASHMAP_H

#include "arraylist.h"

typedef struct HashMap HashMap;

typedef struct Pair
{
    void *key;
    void *value;
} Pair;

struct HashMap
{
    ArrayList *buckets;
    size_t size;
    HashFunction hash;
};

typedef int (*HashFunction)(const void *key);

HashMap *createMap(const size_t size, HashFunction hash);

void mapPut(HashMap **mapPtr, void *key, void *value);
void *mapGet(const HashMap *map, const void *key);
void mapRemove(HashMap **mapPtr, const void *key);

void freeMap(HashMap **mapPtr);


int hash(const void *key, HashFunction hash);

#endif