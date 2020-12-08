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

_Bool LL_add(char *note,  List *list_p)
{

    Node *new = (Node *)malloc(sizeof(Node));
    Node *tmp = *list_p;
        
    //printf("made node\n");
    new->next = NULL;
    strcpy(new->note.data, note);

    if(tmp == NULL) /* if this is the first time calling    */
    {
        *list_p = new;  /* make this the head   */
        return true;    /* leave, nothing more to do    */
    }

//printf("copied\n");

    /*
        list_p = NULL


        List = Node *
        list_p = Node **
        Node * tmp = *list_p
    */
   // printf("Made temp\n");
    
    for (; tmp->next != NULL; tmp = tmp->next);
    //{printf("test\n");}
    
    tmp->next = new;
   // printf("ayo\n");

    return true;
}

void LL_print( List *list_p)
{
    printf("start_print\n");
    Node *tmp;
    size_t index = 1;

    for (tmp = *list_p; tmp != NULL; tmp = tmp->next, index++)
    {
        /*  print -- could make a function pointer  
            and have this as all purpose function   */
        printf("%zd:  %s", index, tmp->note.data);
    }
        printf("\nend_print\n");
}

_Bool LL_delete(int position, List *list_p)
{
    Node *tmp;
    int i = 0;
    /* TODO FIX THIs    */
    if (position > LL_num(list_p))
    {
        return false;
    }
    if (position == 1)
    {
        Node * del_store = *list_p;
        *list_p = (*list_p)->next;
        free(del_store);
    }
    
    printf("pos = %d\n", position);
    
    tmp = *list_p;
    while (tmp != NULL && i < position-2)
    {
        tmp = tmp->next;
        i++;
    }
    printf("on item: %s\n", tmp->note.data);
    if (tmp->next != NULL)
    {
       // Node * del_store = tmp->next;
        tmp->next = (tmp->next)->next;
        //free(del_store);
    }   
    // free deleted item
}

size_t LL_num( List * list_p )
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

void LL_febreeze( List * list_p )
{
    Node * ahead;

    for (; *list_p != NULL; *list_p = ahead)
    {
        ahead = (*list_p)->next;
        free(*list_p);
    }
}
