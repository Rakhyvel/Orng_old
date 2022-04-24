/*
    Maps are used to associate string names with pieces of data. They can give 
    almost instantaneous lookup capabilities. 
    
    Author: Joseph Shimel test
    Date: 11/4/20 
*/

#include "./map.h"
#include "./debug.h"
#include "./list.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(const char*);
void addNode(struct map* map, char* key, void* value, int hash);

/*
    Creates a map pointer */
struct map* Map_Create()
{
    struct map* map = (struct map*)malloc(sizeof(struct map));
    map->size = 0;
    map->capacity = 10;
    map->lists = (struct mapNode**)calloc(map->capacity, sizeof(struct mapNode*));
    map->keyList = List_Create();
    return map;
}

/*
    Destroys a map pointer.
    
    WARNING! The data pointed to by the map will NOT be freed. Make sure to
    free data before hand! (or it'll be bad)  */
void Map_Destroy(struct map* map)
{
    ASSERT(map != NULL);
    for (int i = 0; i < map->capacity; i++) {
        if (!map->lists[i]) {
            struct mapNode* curr = map->lists[i];
            while (curr != NULL) {
                struct mapNode* freeMe = curr;
                curr = curr->next;
                free(freeMe);
            }
        }
    }
    free(map);
}

/*
    Associates a string value with a pointer value in the map 
    
    Returns 1 if key was already in map, 0 if not */
int Map_Put(struct map* map, char* key, void* value)
{
    ASSERT(map != NULL);
    ASSERT(key != NULL);
    unsigned int hashcode = abs(hash(key)) % map->capacity;
    struct mapNode* bucket = map->lists[hashcode];

    if (bucket == NULL) {
        addNode(map, key, value, hashcode);
    } else if (Map_Get(map, key) == NULL) {
        addNode(map, key, value, hashcode);
    } else {
        return 1;
    }
    map->size++;
    return 0;
}

/*
    Returns a the pointer associated with a given string key. Returns NULL if 
    key is not in map. */
void* Map_Get(struct map* map, const char* key)
{
    ASSERT(map != NULL);
    ASSERT(key != NULL);
    unsigned int hashcode = abs(hash(key)) % map->capacity;
    struct mapNode* bucket = map->lists[hashcode];
    if (bucket == NULL) {
        return NULL;
    } else {
        struct mapNode* curr = bucket;
        while (curr != NULL) {
            if (strcmp(curr->key, key) == 0) {
                return curr->value;
            }
            curr = curr->next;
        }
    }
    return NULL;
}

/*
    Returns list of keys in a map ORDERED by when they were added to map! */
struct list* Map_GetKeyList(struct map* map)
{
    return map->keyList;
}

/*
    Copies the elements from one map into another, in the same order they 
    were added to the original map.
    
    Duplicates are NOT added twice, the original is kept */
void Map_Copy(struct map* dst, struct map* src)
{
    struct list* srcList = src->keyList;
    struct listElem* elem;
    for (elem = List_Begin(srcList); elem != List_End(srcList); elem = List_Next(elem)) {
        Map_Put(dst, elem->data, Map_Get(src, elem->data));
    }
}

/*
    Adds a string to the set */
int Set_Add(struct map* set, char* key)
{
    return Map_Put(set, key, (void*)1);
}

/*
    Returns whether or not the given string is in the set */
int Set_Contains(struct map* set, const char* key)
{
    return Map_Get(set, key) != NULL;
}

/*
    Adds a node to a map, and the key to the keylist */
void addNode(struct map* map, char* key, void* value, int hash)
{
    struct mapNode* node = (struct mapNode*)malloc(sizeof(struct mapNode));
    node->key = key;
    node->value = value;
    node->next = map->lists[hash];
    map->lists[hash] = node;
    List_Append(map->keyList, key);
}

/*
    Function that converts every string to an almost unique number.
    
    Shamelessly copied from somewhere on StackOverflow */
int hash(const char* str)
{
    ASSERT(str != NULL);
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = hash * 33 + c;

    return hash;
}
/*
    Returns whether or not a map contains a key */
bool Map_Contains(struct map* map, const char* key)
{
    if (!key) {
        PANIC("KEY IS NULL\n");
    }
    if (!map) {
        PANIC("MAP IS NULL\n");
    }
    for (struct mapNode* bucket = map->lists[hash(key)]; bucket != NULL; bucket = bucket->next) {
        if (!strcmp(bucket->key, key)) {
            return true;
        }
    }
    return false;
}