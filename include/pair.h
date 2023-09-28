#ifndef PAIR_H
#define PAIR_H

typedef struct Pair
{
    void *key;
    void *value;
} Pair;

Pair *createPair(void *key, void *value);

#endif