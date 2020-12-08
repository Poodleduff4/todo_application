#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LEN 50

typedef struct item_st
{
    char data[MAX_LEN];
    time_t creation_time;

} Item;

typedef struct node_st
{
    Item note;
    struct node_st *next;
} Node;

typedef Node *List;

void LL_init(List *list_p);

_Bool LL_add(char *note, List *list_p);

void LL_print(List *list_p);

_Bool LL_delete(int position, List *list_p);

size_t LL_num(List *list_p);

void LL_febreeze(List *list_p);

#endif