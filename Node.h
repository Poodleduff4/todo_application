#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LEN 50
#define MAX_TAG_LEN 10
#define MAX_DATE 11

typedef struct item_st
{
    char data[MAX_LEN];
    char tag[MAX_TAG_LEN];
    char date[MAX_DATE];

} Item;

typedef struct node_st
{
    Item note;
    struct node_st *next;
} Node;

typedef Node *List;

void LL_init(List *list_p);

_Bool LL_add(char *note, char *tag, char *date, List *list_p);

void LL_print(List *list_p);

_Bool LL_delete(int position, List *list_p);

size_t LL_num(List *list_p);

void LL_febreeze(List *list_p);

void LL_sort_date(List *list_p);

void LL_swap(List *list_p, Node *prev, Node *pos, int first_pos);

Node *LL_get_pos(List *list_p, int pos);


int compare_dates(char *date1, char *date2);

#endif