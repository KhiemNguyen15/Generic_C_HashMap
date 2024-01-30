#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "arraylist.h"
#include "hashmap.h"
#include "pair.h"

#define HASHCONSTANT 0.6180339887
#define GETBUCKET                                                              \
  size_t hashCode = hash(map, key, map->convert);                              \
  ArrayList *bucket = listGet(map->buckets, hashCode);

#define MALLOCCHECK(ptr)                                                       \
  do {                                                                         \
    if (ptr == NULL) {                                                         \
      fprintf(stderr, "Memory allocation failed.\n");                          \
      free(ptr);                                                               \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

HashMap *createMap(const size_t size, ConvertFunction convert,
                   EqualityFunction comparePairKeys) {
  HashMap *newMap = (HashMap *)malloc(sizeof(HashMap));
  MALLOCCHECK(newMap);

  ArrayList *keys = createList();
  ArrayList *buckets = createList();
  newMap->size = size;
  for (int i = 0; i < newMap->size; i++) {
    ArrayList *bucket = createList();
    listAdd(&buckets, bucket);
  }
  newMap->buckets = buckets;
  newMap->keys = keys;
  newMap->mappings = 0;
  newMap->convert = convert;
  newMap->comparePairKeys = comparePairKeys;

  return newMap;
}

HashMap *mapClone(const HashMap *toClone) {
  HashMap *newMap =
      createMap(toClone->size, toClone->convert, toClone->comparePairKeys);
  mapPutAll(&newMap, toClone);

  return newMap;
}

double floorValue(double val) {
  if (val >= 0.0) {
    return (double)((long)val);
  } else {
    double intPart = (double)((long)val);
    return (intPart == val) ? intPart : intPart - 1.0;
  }
}

double frac(double val) { return val - floorValue(val); }

size_t hash(const HashMap *map, const void *key, ConvertFunction convert) {
  double hashCode = floorValue(map->size * frac(convert(key) * HASHCONSTANT));

  return (size_t)hashCode;
}

void mapPut(HashMap **mapPtr, void *key, void *value) {
  HashMap *map = *mapPtr;

  GETBUCKET
  Pair *newPair = createPair(key, value);
  int index = listIndexOf(bucket, newPair, map->comparePairKeys);
  if (index != -1) {
    listSet(&bucket, newPair,
            listIndexOf(bucket, newPair, map->comparePairKeys));
  } else {
    listAdd(&bucket, newPair);
    listAdd(&(map->keys), key);
    map->mappings++;
  }
}

void mapPutIfAbsent(HashMap **mapPtr, void *key, void *value) {
  HashMap *map = *mapPtr;

  GETBUCKET
  Pair *newPair = createPair(key, value);
  int index = listIndexOf(bucket, newPair, map->comparePairKeys);
  if (index == -1) {
    listAdd(&bucket, newPair);
    listAdd(&(map->keys), key);
    map->mappings++;
  }
}

void mapPutAll(HashMap **mapPtr, const HashMap *toPut) {
  HashMap *map = *mapPtr;

  for (int i = 0; i < listSize(toPut->keys); i++) {
    mapPut(&map, listGet(toPut->keys, i),
           mapGet(toPut, listGet(toPut->keys, i)));
  }
}

void mapReplace(HashMap **mapPtr, void *key, void *value) {
  HashMap *map = *mapPtr;

  GETBUCKET
  Pair *newPair = createPair(key, value);
  int index = listIndexOf(bucket, newPair, map->comparePairKeys);
  if (index != -1) {
    listSet(&bucket, newPair,
            listIndexOf(bucket, newPair, map->comparePairKeys));
  }
}

void mapRemove(HashMap **mapPtr, void *key) {
  HashMap *map = *mapPtr;

  GETBUCKET
  Pair *toFind = createPair(key, NULL);
  int index = listIndexOf(bucket, toFind, map->comparePairKeys);
  if (index != -1) {
    listRemove(&bucket, index);
    map->mappings--;

    for (int i = 0; i < listSize(map->keys); i++) {
      if (!mapContainsKey(map, listGet(map->keys, i))) {
        listRemove(&(map->keys), i);
        break;
      }
    }
  }
}

void mapClear(HashMap **mapPtr) {
  HashMap *map = *mapPtr;

  for (int i = 0; i < map->size; i++) {
    ArrayList *bucket = listGet(map->buckets, i);
    listClear(&bucket);
  }
  map->mappings = 0;
  listClear(&(map->keys));
}

void *mapGet(const HashMap *map, void *key) {
  GETBUCKET
  Pair *toFind = createPair(key, NULL);
  int index = listIndexOf(bucket, toFind, map->comparePairKeys);
  if (index != -1) {
    Pair *toReturn = (Pair *)listGet(bucket, index);
    return toReturn->value;
  }

  return NULL;
}

void *mapGetOrDefault(const HashMap *map, void *key, void *defaultValue) {
  GETBUCKET
  Pair *toFind = createPair(key, NULL);
  int index = listIndexOf(bucket, toFind, map->comparePairKeys);
  if (index != -1) {
    Pair *toReturn = (Pair *)listGet(bucket, index);
    return toReturn->value;
  }

  return defaultValue;
}

ArrayList *mapGetKeys(const HashMap *map) { return map->keys; }

ArrayList *mapGetValues(const HashMap *map) {
  ArrayList *values = createList();

  for (int i = 0; i < listSize(map->keys); i++) {
    listAdd(&values, mapGet(map, listGet(map->keys, i)));
  }

  return values;
}

size_t mapSize(const HashMap *map) { return map->mappings; }

bool mapContainsKey(const HashMap *map, void *key) {
  GETBUCKET
  Pair *toFind = createPair(key, NULL);
  return listContains(bucket, toFind, map->comparePairKeys);
}

bool mapContainsValue(const HashMap *map, void *value,
                      EqualityFunction compare) {
  for (int i = 0; i < listSize(map->keys); i++) {
    if (compare(mapGet(map, listGet(map->keys, i)), value)) {
      return true;
    }
  }
  return false;
}

bool mapIsEmpty(const HashMap *map) { return map->mappings == 0; }

void freeMap(HashMap **mapPtr) {
  HashMap *map = *mapPtr;

  for (int i = 0; i < listSize(map->buckets); i++) {
    ArrayList *toFree = listGet(map->buckets, i);
    freeList(&toFree);
  }
  freeList(&(map->buckets));
  free(map);
}
