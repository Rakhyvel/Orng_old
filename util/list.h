#ifndef List_H
#define List_H

#include <stdbool.h>

#define forall(e, l) for (ListElem* e = List_Begin(l); e != List_End(l); e = e->next)

// Doubly linked list node
struct listElem {
    struct listElem* next;
    struct listElem* prev;
    void* data;
};
typedef struct listElem ListElem;
// Doubly linked list, with head and tail
struct list {
    struct listElem head;
    struct listElem tail;
    int size;
};
typedef struct list List;

List* List_Create();
void List_Destroy(List* list);
List* List_Concat(List* a, List* b);
struct listElem* List_Begin(struct list*);
struct listElem* List_Next(struct listElem*);
struct listElem* List_End(struct list*);
void List_Insert(List* list, ListElem* before, void* data);
void List_Append(List* list, void* data);
void List_Push(List* list, void* data);
void* List_Get(List* list, int i);
void* List_Peek(List* list);
void* List_Pop(List* list);
bool List_IsEmpty(List* list);
bool List_Contains(List* list, void* data);

#endif