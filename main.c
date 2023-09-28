#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <hashmap.h>

long convert(const void *key)
{
    //printf("key:%ld\n", *(long*)key);
    return *(long *)key;
}

bool comparePairKeys(const void *a, const void *b)
{
    Pair pairA = *(Pair *)a;
    Pair pairB = *(Pair *)b;

    return *(int *)pairA.key == *(int *)pairB.key;
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

    long key1 = 100;
    long key2 = 200;
    char *person = "Charles";
    //long *newKey = &key;
    //printf("key:%ld\n", *newKey);
    mapPut(&map, &key1, person);
    mapPut(&map, &key2, "Something");

    printf("%s\n", (char *)mapGet(map, &key1));
    printf("%s\n", (char *)mapGet(map, &key2));


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