# Generic Type Hash Map Documentation

## Introduction

This C library provides a hash map implementation that allows you to store and manage key-value pairs of any type. The library provides functions to create and manipulate hash maps dynamically. It uses a hash table to efficiently store and retrieve key-value pairs, making it suitable for a wide range of applications where fast key-value lookups are required.

## Getting Started

### Including the Library

```c
#include <hashmap.h>
```

### Creating a HashMap

```c
HashMap *createMap(const size_t size, ConvertFunction convert, EqualityFunction comparePairKeys)
```

Usage:

```c
HashMap *map = createMap(size, convertFunction, compareFunction);
```

* Creates a new empty hash map.
* `size`: The initial size of the hash map.
* `convertFunction`: A function to convert keys into a long integer for hashing.
* `compareFunction`: A function to compare keys for equality.
* Returns a pointer to the newly created hash map.

### Cloning a HashMap

```c
HashMap *mapClone(const HashMap *toClone)
```

Usage:

```c
HashMap *newMap = mapClone(map);
```

* Creates a new hash map that is a deep copy of an existing hash map.
* `toClone`: A pointer to the hash map you want to clone.
* Returns a pointer to the newly created hash map.

## Function Pointers

### Equality Function
```c
typedef bool (*EqualityFunction)(const void *, const void *);
```

* A function to compare elements for equality.

### Convert Function

```c
typedef long (*ConvertFunction)(const void *key);
```

* A function to convert keys into a long integer for hashing.

## Basic Operations

### Putting a Key-Value Pair

```c
void mapPut(HashMap **mapPtr, void *key, void *value)
```

Usage:

```c
mapPut(&map, key, value);
```

* Inserts a key-value pair into the hash map.
* If the key already exists, the value associated with the key is updated.
* `key`: A pointer to the key.
* `value`: A pointer to the value associated with the key.

### Putting a Key-Value Pair if Absent

```c
void mapPutIfAbsent(HashMap **mapPtr, void *key, void *value)
```

Usage:

```c
mapPutIfAbsent(&map, key, value);
```

* Inserts a key-value pair into the hash map only if the key does not already exist in the map.
* `key`: A pointer to the key.
* `value`: A pointer to the value associated with the key.

### Putting All Key-Value Pairs from Another HashMap

```c
void mapPutAll(HashMap **mapPtr, const HashMap *toPut)
```

Usage:

```c
mapPutAll(&map, otherMap);
```

* Inserts all key-value pairs from another hash map into the current hash map.
* `toPut`: A pointer to the hash map containing key-value pairs to be inserted.

### Replacing a Key-Value Pair

```c
void mapReplace(HashMap **mapPtr, void *key, void *value)
```

Usage:

```c
mapReplace(&map, key, value);
```

* Replaces the value associated with a key in the hash map.
* If the key does not exist in the map, no action is taken.
* `key`: A pointer to the key.
* `value`: A pointer to the new value associated with the key.

### Removing a Key-Value Pair

```c
void mapRemove(HashMap **mapPtr, void *key)
```

Usage:

```c
mapRemove(&map, key);
```

* Removes a key-value pair from the hash map based on the specified key.
* If the key does not exist in the map, no action is taken.
* `key`: A pointer to the key to be removed.

### Clearing the HashMap

```c
void mapClear(HashMap **mapPtr)
```

Usage:

```c
mapClear(&map);
```

* Removes all key-value pairs from the hash map, making it empty.

## Querying the HashMap

### Getting the Value for a Key

```c
void *mapGet(const HashMap *map, void *key)
```

Usage:

```c
void *value = mapGet(map, key);
```

* Retrieves the value associated with a key from the hash map.
* If the key does not exist in the map, `NULL` is returned.
* `key`: A pointer to the key for which you want to retrieve the value.

### Getting the Value for a Key with Default

```c
void *mapGetOrDefault(const HashMap *map, void *key, void *defaultValue)
```

Usage:

```c
void *value = mapGetOrDefault(map, key, defaultValue);
```

* Retrieves the value associated with a key from the hash map.
* If the key does not exist in the map, the specified default value is returned.
* `key`: A pointer to the key for which you want to retrieve the value.
* `defaultValue`: The value to return if the key is not found in the map.

### Getting All Keys

```c
ArrayList *mapGetKeys(const HashMap *map)
```

Usage:

```c
ArrayList *keys = mapGetKeys(map);
```

* Returns an ArrayList containing all the keys in the hash map.

### Getting All Values

```c
ArrayList *mapGetValues(const HashMap *map)
```

Usage:

```c
ArrayList *values = mapGetValues(map);
```

* Returns an ArrayList containing all the values in the hash map.

### Getting the Size

```c
size_t mapSize(const HashMap *map)
```

Usage:

```c
size_t size = mapSize(map);
```

* Returns the current number of key-value pairs in the hash map.

### Checking if a Key Exists

```c
bool mapContainsKey(const HashMap *map, void *key)
```

Usage:

```c
bool exists = mapContainsKey(map, key);
```

* Checks if a key exists in the hash map.
* Returns `true` if the key exists; otherwise, returns `false`.
* `key`: A pointer to the key to check for existence.

### Checking if a Value Exists

```c
bool mapContainsValue(const HashMap *map, void *value, EqualityFunction compare)
```

Usage:

```c
bool exists = mapContainsValue(map, value, compareFunction);
```

* Checks if a value exists in the hash map.
* Returns `true` if the value exists; otherwise, returns `false`.
* `value`: A pointer to the value to check for existence.
* `compareFunction`: A function to compare values for equality.

### Checking if the HashMap is Empty

```c
bool mapIsEmpty(const HashMap *map)
```

Usage:

```c
bool isEmpty = mapIsEmpty(map);
```

* Checks if the hash map is empty.
* Returns `true` if the hash map is empty; otherwise, returns `false`.

## Memory Management

### Freeing the HashMap

```c
void freeMap(HashMap **mapPtr)
```

Usage:

```c
freeMap(&map);
```

* Frees the memory associated with the hash map.
* This should be called when you are done using the hash map to prevent memory leaks.

## Error Handling

* The library includes error handling for memory allocation failures. If memory allocation fails during the creation of a hash map, an error message is printed to `stderr`, and the program exits.

## Example Usage

Below is an example of how to use the hash map library:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <hashmap.h>

// Function that converts the key to a long integer for hashing
long convertKey(const void *key) 
{
    return (long)(*(int *)key);
}

// Function to compare the keys of each key-value pair
bool compareKeys(const void *a, const void *b) 
{
    Pair pairA = *(Pair *)a;
    Pair pairB = *(Pair *)b;

    return *(int *)pairA.key == *(int *)pairB.key;
}

int main() 
{
    // Create a hash map with custom key handling
    HashMap *map = createMap(10, convertKey, compareKeys);

    // Populate the hash map
    int key1 = 42;
    int value1 = 100;
    mapPut(&map, &key1, &value1);

    // Retrieve a value
    int *retrievedValue = (int *)mapGet(map, &key1);
    if (retrievedValue != NULL) 
    {
        printf("Retrieved value for key1: %d\n", *retrievedValue);
    } else 
    {
        printf("Key1 not found.\n");
    }

    // Check if a key exists
    bool key1Exists = mapContainsKey(map, &key1);
    printf("Key1 exists: %s\n", key1Exists ? "true" : "false");

    // Add more key-value pairs
    int key2 = 55;
    int value2 = 200;
    int key3 = 30;
    int value3 = 300;

    mapPut(&map, &key2, &value2);
    mapPut(&map, &key3, &value3);

    // Get all keys and values
    ArrayList *keys = mapGetKeys(map);
    ArrayList *values = mapGetValues(map);

    printf("\nAll keys in the map:\n");
    for (int i = 0; i < listSize(keys); i++) 
    {
        int *currentKey = (int *)listGet(keys, i);
        printf("%d\n", *currentKey);
    }

    printf("\nAll values in the map:\n");
    for (int i = 0; i < listSize(values); i++) 
    {
        int *currentValue = (int *)listGet(values, i);
        printf("%d\n", *currentValue);
    }

    // Update a value
    int newValueForKey2 = 999;
    mapReplace(&map, &key2, &newValueForKey2);

    printf("\nUpdated value for key2: %d\n", *(int *)mapGet(map, &key2));

    // Remove a key-value pair
    mapRemove(&map, &key3);
    bool key3Exists = mapContainsKey(map, &key3);
    printf("Key3 exists after removal: %s\n", key3Exists ? "true" : "false");

    // Check if the map is empty
    bool isEmpty = mapIsEmpty(map);
    printf("Is the map empty: %s\n", isEmpty ? "true" : "false");

    // Free memory
    freeMap(&map);
    freeList(&keys);
    freeList(&values);

    return 0;
}
```

# Compilation Guide

This guide provides instructions on how to compile and build the project containing the HashMap library. The project consists of source code located in the `src` directory, header files in the `include` directory, and a main source file. Compilation is managed using a Makefile that uses the GCC compiler.

## Prerequisites

Before you can compile, ensure that you have the following prerequisites installed on your system:

* GCC (GNU Compiler Collection)
* Standard C Library (libc) development files (usually provided by the libc-dev package on Linux systems)
* (Optional) Make (Build automation tool)

## Compilation Steps With Make

Follow these steps to compile:

1. **Clone the Repository:** If you haven't already, clone the repository containing the project.

2. **Navigate to the Project Directory:** Change your current directory to the project root.

3. **Compile the Program:** Run the `make` command to compile the program. The Makefile will automatically locate source files in the `src` directory, `include` header files from the include directory, and produce an executable.

    ```bash
    make
    ```

    If you encounter any errors during compilation, make sure you have met the prerequisites and resolved any issues.

4. **Clean Up (Optional):** To clean the build directory and remove compiled files and executables, you can use the following command:

    ```bash
    make clean
    ```

    This will delete all generated object files and the executable.

## Compilation Steps Without Make

Follow these steps to compile:

1. **Clone the Repository:** If you haven't already, clone the repository containing your project.

2. **Navigate to the Project Directory:** Change your current directory to the project root.

3. **Compile the Program:** Use the following `gcc` command to compile your program:

    ```bash
    gcc -I./include -o hashmaprunner main.c src/data.c src/arraylist.c src/pair.c src/hashmap.c
    ```

    Replace `hashmaprunner` with the desired executable name if you wish to do so.

    If you encounter any errors during compilation, make sure you have met the prerequisites and resolved any issues.

    Replace `main.c` with the actual name of your main source file if it's different. Additionally, make sure you adjust the compilation command as needed to include any other source files in your project.
