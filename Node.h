#ifndef NODE_H_
#define NODE_H_

#include <stdbool.h>

#define MAX_LEN 50

typedef struct item_st
{
    char data[MAX_LEN];

} Item;

typedef struct node_st
{
    Item note;
    struct node_st *next;
} Node;

typedef Node *List;

void LL_init(List *list_p);

_Bool LL_add(char * note, List *list_p);

void LL_print(const List *list_p);

#endif