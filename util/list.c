/*  list.c

    A doubley linked list, where nodes have references both to the node that 
    comes before and after them in the list. Can represent both stacks, queues,
    or just regular lists.

    Author: Joseph Shimel
    Date: 6/21/21
*/

#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

/*  Creates a new list, with no new nodes. */
List* List_Create()
{
    List* list = (List*)calloc(1, sizeof(struct list));

    list->head.next = &list->tail;
    list->tail.prev = &list->head;

    return list;
}

// Empty the list but do not free the data
void List_Clear(List* list)
{
    ListElem* toFree = NULL;
    forall(elem, list)
    {
        if (toFree) {
            free(toFree);
        }
        toFree = elem;
    }
    if (toFree) {
        free(toFree);
    }
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
}

List* List_Concat(List* a, List* b)
{
    if (a == NULL && b != NULL) {
        return b;
    } else if (a != NULL && b == NULL) {
        return a;
    } else if (a == NULL && b == NULL) {
        return a;
    } else {
        a->tail.prev->next = b->head.next;
        b->head.next->prev = a->tail.prev;
        b->tail.prev->next = &a->tail;
        a->tail = b->tail;
        a->size += b->size;
        return a;
    }
}

/*  Gives the starting point of the list */
struct listElem* List_Begin(struct list* list)
{
    return list->head.next;
}

/*  Returns the next list element */
struct listElem* List_Next(struct listElem* elem)
{
    return elem->next;
}

/*  Returns the tail of the linked list, can be used to detect when a loop has
    reached the end of the list during traversal */
struct listElem* List_End(struct list* list)
{
    return &list->tail;
}

/*
    Inserts a new list element after a given list element. */
void List_Insert(List* list, ListElem* before, void* data)
{
    ListElem* elem = (ListElem*)malloc(sizeof(struct listElem));
    elem->data = data;
    elem->prev = before->prev;
    elem->next = before;
    before->prev->next = elem;
    before->prev = elem;
    list->size++;
}

/*
    Appends data to the end of a given list */
void List_Append(List* list, void* data)
{
    List_Insert(list, &list->tail, data);
}

void List_Remove(List* list, void* data)
{
    forall(elem, list)
    {
        if (elem->data == data) {
            elem->prev->next = elem->next;
            elem->next->prev = elem->prev;
            list->size--;
            return;
        }
    }
}

/*
    Prepends data to the begining of a given list */
void List_Push(List* list, void* data)
{
    List_Insert(list, list->head.next, data);
}

/*
    Returns the data at a given index of a list */
void* List_Get(List* list, int i)
{
    ListElem* elem = list->head.next;
    for (; i > 0 && elem != &list->tail; i--, elem = elem->next)
        ;
    return elem->data;
}

/*
    Returns the data at the begining of a list */
void* List_Peek(List* list)
{
    return list->head.next->data;
}

/* Removes the first element in the list, returns data pointer */
void* List_Pop(List* list)
{
    ListElem* elem = list->head.next;
    ListElem* next = list->head.next->next;
    void* retval = list->head.next->data;

    // Swap pointers, free old node
    list->head.next = next;
    next->prev = &(list->head);
    free(elem);

    list->size--;

    return retval;
}

/*
    Returns whether or not a list is empty */
bool List_IsEmpty(List* list)
{
    return list->head.next == &list->tail;
}

/*
    Frees the values in a list, and then frees the list struct itself. */
void List_Destroy(List* list)
{
    while (!List_IsEmpty(list)) {
        free(List_Pop(list));
    }
    free(list);
}

bool List_Contains(List* list, void* data)
{
    for (ListElem* e = List_Begin(list); e != List_End(list); e = e->next) {
        if (e->data == data) {
            return true;
        }
    }
    return false;
}

bool Set_Put(List* list, void* data)
{
    forall(elem, list)
    {
        if (elem->data == data) {
            return false;
        }
    }
    List_Append(list, data);
    return true;
}