#ifndef HASHMAP_H
#define HASHMAP_H

#include "arraylist.h"
#include "pair.h"

typedef struct HashMap HashMap;

// A function to convert keys into a long integer for hashing.
typedef long (*ConvertFunction)(const void *key);

struct HashMap
{
    ArrayList *buckets;
    ArrayList *keys;
    size_t size;
    size_t mappings;
    ConvertFunction convert;
    EqualityFunction comparePairKeys;
};

// Creates a new empty hash map.
HashMap *createMap(const size_t size, ConvertFunction convert, EqualityFunction comparePairKeys);
// Creates a new hash map that is a deep copy of an existing hash map.
HashMap *mapClone(const HashMap *toClone);

// Inserts a key-value pair into the hash map.
void mapPut(HashMap **mapPtr, void *key, void *value);
// Inserts a key-value pair into the hash map only if the key does not already exist in the map.
void mapPutIfAbsent(HashMap **mapPtr, void *key, void *value);
// Inserts all key-value pairs from another hash map into the current hash map.
void mapPutAll(HashMap **mapPtr, const HashMap *toPut);
// Replaces the value associated with a key in the hash map.
void mapReplace(HashMap **mapPtr, void *key, void *value);
// Removes a key-value pair from the hash map based on the specified key.
void mapRemove(HashMap **mapPtr, void *key);
// Removes all key-value pairs from the hash map, making it empty.
void mapClear(HashMap **mapPtr);

// Retrieves the value associated with a key from the hash map.
void *mapGet(const HashMap *map, void *key);
// Retrieves the value associated with a key from the hash map; returns the specified default value if the key does not exist.
void *mapGetOrDefault(const HashMap *map, void *key, void *defaultValue);
// Returns an ArrayList containing all the keys in the hash map.
ArrayList *mapGetKeys(const HashMap *map);
// Returns an ArrayList containing all the values in the hash map.
ArrayList *mapGetValues(const HashMap *map);
// Returns the current number of key-value pairs in the hash map.
size_t mapSize(const HashMap *map);
// Checks if a key exists in the hash map.
bool mapContainsKey(const HashMap *map, void *key);
// Checks if a value exists in the hash map.
bool mapContainsValue(const HashMap *map, void *value, EqualityFunction compare);
// Checks if the hash map is empty.
bool mapIsEmpty(const HashMap *map);

// Frees the memory associated with the hash map.
void freeMap(HashMap **mapPtr);

#endif