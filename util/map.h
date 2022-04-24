#ifndef MAP_H
#define MAP_H

#include "./list.h"

struct mapNode {
	char* key;
	void* value;
	struct mapNode* next;
};

// Maps text to void pointers
typedef struct map {
	int size;
	int capacity;
	struct mapNode** lists;
	struct list* keyList;
} Map;

struct map* Map_Create();
void Map_Destroy(struct map*);
int Map_Put(struct map*, char*, void*);
void* Map_Get(struct map*, const char*);
struct list* Map_GetKeyList(struct map* map);
void Map_Copy(struct map*, struct map*);
int Set_Add(struct map*, char*);
int Set_Contains(struct map*, const char*);
bool Map_Contains(struct map* map, const char* key);

#endif
