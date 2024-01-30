#include <stdlib.h>

#include "pair.h"

Pair *createPair(void *key, void *value) {
  Pair *newPair = (Pair *)malloc(sizeof(Pair));
  newPair->key = key;
  newPair->value = value;

  return newPair;
}
