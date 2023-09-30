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

    int grade1 = 100;
    int grade2 = 97;
    int grade3 = 84;
    int grade4 = 32;

    mapPut(&map, &key1, "Charles");
    mapPut(&map, &key2, "Something");
    mapPut(&map, &key2, "Nothing");
    mapPut(&map, &key3, "Collision");

    mapPut(&strMap, "James", &grade1);
    mapPut(&strMap, "Juan", &grade2);
    mapPut(&strMap, "Jacob", &grade3);
    mapPut(&strMap, "Joe", &grade4);

    printf("Long Key Map:\n");
    printf("%s\n", (mapGet(map, &key1) != NULL) ? (char *)mapGet(map, &key1) : "NULL");
    printf("%s\n", (mapGet(map, &key2) != NULL) ? (char *)mapGet(map, &key2) : "NULL");
    printf("%s\n", (mapGet(map, &key3) != NULL) ? (char *)mapGet(map, &key3) : "NULL");

    printf("\nString Key Map:\n");
    printf("%d\n", (mapGet(strMap, "James") != NULL) ? *(int *)mapGet(strMap, "James") : -1);
    printf("%d\n", (mapGet(strMap, "Juan") != NULL) ? *(int *)mapGet(strMap, "Juan") : -1);
    printf("%d\n", (mapGet(strMap, "Jacob") != NULL) ? *(int *)mapGet(strMap, "Jacob") : -1);
    printf("%d\n", (mapGet(strMap, "Joe") != NULL) ? *(int *)mapGet(strMap, "Joe") : -1);

    printf("String Map Contains JoeMama: %s\n", (mapGet(strMap, "JoeMama")) ? "Yes" : "No");

    /* 
    ArrayList *bucket = (ArrayList *)listGet(map->buckets, 6);
    Pair *pair = (Pair *)listGet(bucket, 0); 
    if(pair == NULL)
        printf("%s\n", "NULL");
    else printf("%s\n", (char *)pair->value);

    mapGet(map, &key2);
    */

    /*
    mapPut(&map, (int *)100, (char *)"Zach");
    mapPut(&map, (int *)0, (char *)"Jason");
    mapPut(&map, (int *)102, (char *)"Zip");
    mapPut(&map, (int *)63, (char *)"John");
    mapPut(&map, (int *)83, (char *)"Jacob");
    mapPut(&map, (int *)30, (char *)"Nick");
    */

    //char *name = (char *)malloc(100 * sizeof(char));
    

    //printf("%s\n", (char *)mapGet(map, &key1));
    //printf("%s\n", (char *)mapGet(map, &key2));

    //printf("%s\n", name);

    //char *name = (char *)mapGet(map, (long *)100);
    //printf("%s\n", name);

    //mapRemove(&map, (long *)30);

    //printMap(map);

    freeMap(&map);
    return 0;
}