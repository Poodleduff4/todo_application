#include "Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

void LL_init(List *list_p)
{
    *list_p = NULL;
}

_Bool LL_add(char *note, char *tag, char *date, List *list_p)
{

    Node *new = (Node *)malloc(sizeof(Node));
    Node *tmp = *list_p;

    //printf("made node\n");
    new->next = NULL;
    strcpy(new->note.data, note);
    strcpy(new->note.tag, tag);
    strcpy(new->note.date, date);

    if (tmp == NULL) /* if this is the first time calling    */
    {
        *list_p = new; /* make this the head   */
        return true;   /* leave, nothing more to do    */
    }

    //printf("copied\n");

    /*
        list_p = NULL


        List = Node *
        list_p = Node **
        Node * tmp = *list_p
    */
    // printf("Made temp\n");

    for (; tmp->next != NULL; tmp = tmp->next)
        ;
    //{printf("test\n");}

    tmp->next = new;
    // printf("ayo\n");

    return true;
}

void LL_print(List *list_p)
{
    Node *tmp;
    size_t index = 0;

    for (tmp = *list_p; tmp != NULL; tmp = tmp->next, index++)
    {
        /*  print -- could make a function pointer  
            and have this as all purpose function   */
        printf("%zd:  note: %s\ntag: %s\ndate: %s\n", index, tmp->note.data, tmp->note.tag, tmp->note.date);
    }
}

_Bool LL_delete(int position, List *list_p)
{
    Node *tmp = *list_p;

    if (position == 0)
    {
        *list_p = (*list_p)->next;
        free(tmp);
        return true;
    }

    for (int i = 0; tmp != NULL && i < (position - 1); i++, tmp = tmp->next)
        ;

    if (tmp->next == NULL)
    {
        fprintf(stderr, "nothing to delete here, idiot, at pos [%d]\n", position);
        return false;
    }

    Node *del_store = tmp->next;
    tmp->next = del_store->next;
    free(del_store);

    if (tmp->next != NULL)
    {
        printf("reassigned [%s] to point to [%s]\n", tmp->note.data, (tmp->next)->note.data);
    }
    else
    {
        printf("reassigned [%s] to point to [NULL]", tmp->note.data);
    }
    return true;
}

void LL_sort_tag(List *list_p)
{
    /* not sorting the array directly in place   */
    /* problem because if this is out of place then */
}

size_t LL_num(List *list_p)
{
    size_t count = (size_t)0;
    Node *tmp;
    for (tmp = *list_p; tmp != NULL; tmp = tmp->next)
    {
        count++;
    }
    // printf("%zd \n", count);
    return count;
}

void LL_febreeze(List *list_p)
{
    Node *ahead;

    for (; *list_p != NULL; *list_p = ahead)
    {
        ahead = (*list_p)->next;
        free(*list_p);
    }
}
