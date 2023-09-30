#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <hashmap.h>

long convert(const void *key)
{
    return *(long *)key;
}

long convertStringKey(const void *key)
{
    char *str = (char *)key;
    long hashKey = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        hashKey += (long)str[i];
    }
    return hashKey;
}

bool comparePairKeys(const void *a, const void *b)
{
    Pair pairA = *(Pair *)a;
    Pair pairB = *(Pair *)b;

    return *(int *)pairA.key == *(int *)pairB.key;
}

bool compareStringKeys(const void *a, const void *b)
{
    Pair pairA = *(Pair *)a;
    Pair pairB = *(Pair *)b;

    return strcmp((char *)pairA.key, (char *)pairB.key) == 0; 
}

void printMap(const HashMap *map)
{
    for(int i = 0; i < listSize(map->buckets); i++)
    {
        printf("Bucket %d:\n", i + 1);
        ArrayList *bucket = listGet(map->buckets, i);
        for(int j = 0; j < listSize(bucket); j++)
            printf("    <%ld, %s>\n", *(long *)((Pair *)(bucket->arr[j]).val)->key, (char *)((Pair *)(bucket->arr[j]).val)->value);
    }
}

int main(int argc, char **argv)
{
    HashMap *map = createMap(10, convert, comparePairKeys);
    HashMap *strMap = createMap(10, convertStringKey, compareStringKeys);

    long key1 = 100;
    long key2 = 200;
    long key3 = 10000000;
    long key4 = 175;

    int grade1 = 100;
    int grade2 = 97;
    int grade3 = 84;
    int grade4 = 32;

    mapPut(&map, &key1, "Charles");
    mapPut(&map, &key2, "Something");
    mapPut(&map, &key3, "Collision");
    mapPut(&map, &key4, "Nothing");
    mapReplace(&map, &key4, "Howdy");

    mapPut(&strMap, "James", &grade1);
    mapPut(&strMap, "Juan", &grade2);
    mapPut(&strMap, "Jacob", &grade3);
    mapPut(&strMap, "Joe", &grade4);

    HashMap *clone = mapClone(map);
    mapRemove(&clone, &key4);

    printf("Long Key Map:\n");
    printf("%s\n", (mapGet(map, &key1) != NULL) ? (char *)mapGet(map, &key1) : "NULL");
    printf("%s\n", (mapGet(map, &key2) != NULL) ? (char *)mapGet(map, &key2) : "NULL");
    printf("%s\n", (mapGet(map, &key3) != NULL) ? (char *)mapGet(map, &key3) : "NULL");
    printf("%s\n", (mapGet(map, &key4) != NULL) ? (char *)mapGet(map, &key4) : "NULL");
    printf("%lu\n", mapSize(map));

    printf("\nClone Key Map:\n");
    printf("%s\n", (mapGet(clone, &key1) != NULL) ? (char *)mapGet(clone, &key1) : "NULL");
    printf("%s\n", (mapGet(clone, &key2) != NULL) ? (char *)mapGet(clone, &key2) : "NULL");
    printf("%s\n", (mapGet(clone, &key3) != NULL) ? (char *)mapGet(clone, &key3) : "NULL");
    printf("%s\n", (mapGet(clone, &key4) != NULL) ? (char *)mapGet(clone, &key4) : "NULL");
    printf("%lu\n", mapSize(clone));

    printf("\nString Key Map:\n");
    printf("%d\n", (mapGet(strMap, "James") != NULL) ? *(int *)mapGet(strMap, "James") : -1);
    printf("%d\n", (mapGet(strMap, "Juan") != NULL) ? *(int *)mapGet(strMap, "Juan") : -1);
    printf("%d\n", (mapGet(strMap, "Jacob") != NULL) ? *(int *)mapGet(strMap, "Jacob") : -1);
    printf("%d\n", (mapGet(strMap, "Joe") != NULL) ? *(int *)mapGet(strMap, "Joe") : -1);
    printf("%lu\n", mapSize(strMap));

    freeMap(&map);
    freeMap(&strMap);
    freeMap(&clone);
    return 0;
}