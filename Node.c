#include "Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LL_init(List *list_p)
{
    *list_p = NULL;
}

_Bool LL_add(char *note, List *list_p)
{
    Node *new = (Node *)malloc(sizeof(Node));
    Node *tmp = list_p;
/*
    if(tmp == NULL)
    {
        *list_p = new;
        return true;
    }
*/
    printf("made node\n");
    strcpy(new->note.data, note);
    printf("copied\n");

    /*
        list_p = NULL


        List = Node *
        list_p = Node **
        Node * tmp = *list_p
    */
    printf("Made temp\n");
    
    for (; tmp->next != NULL; tmp = tmp->next)
    {}
    printf("test\n");
    tmp->next = new;
    printf("ayo\n");

    return true;
}

void LL_print(const List *list_p)
{
    Node *tmp;
    for (tmp = *list_p; tmp != NULL; tmp = tmp->next)
    {
        /*  print -- could make a function pointer  
            and have this as all purpose function   */
        printf("%s\n", tmp->note.data);
    }
}
