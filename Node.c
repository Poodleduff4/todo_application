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

Node *LL_get_pos(List *list_p, int pos)
{

    if (pos < 0)
    {
        fprintf(stderr, "tried to access negative index\n");
        exit(1); /* treat as fatal   */
    }

    /* if (pos > LL_num(list_p))
    {
        fprintf(stderr, "out of bounds access\n");
        exit(1); /* treat as fatal   
}
*/
    printf("pos (int) = %d\n", pos);
    Node *tmp = *list_p;
    for (int i = 0; tmp != NULL && i < (pos + 1); i++, tmp = tmp->next)
    {
        printf("i = %d\n", i);
    }

    return tmp;
}

/* 
for i = 1 to end-1:
    int j = i - 1;
    current = LL_get_pos(i);
    prev_position = LL_get_pos(j);
    while (j >= 0 && prev_position.date > current.date):
        prev_position
        swap prev, pos
        
        prev_position--;
    

0 1 2 prev pos 5 6
       ^ j 
prev > pos

0 1 2 5 6

2.next [prev.before or ] = pos
pos.next = prev
prev.next = 5

*/
void LL_sort_date(List *list_p)
{
    int size_of_list = LL_num(list_p);
    int i = 1;
    int j;
    Node *curr;
    Node *prev;

    for (; i < size_of_list - 1; i++)
    {
        j = i - 1;
        curr = LL_get_pos(list_p, i);
        prev = LL_get_pos(list_p, j);
        printf("in for %d\n", size_of_list);
        while (j >= 0 && compare_dates(prev->note.date, curr->note.date) > 0)
        {
            puts("in while");
            LL_swap(list_p, LL_get_pos(list_p, j), LL_get_pos(list_p, j + 1), j);
            j--;
        }
    }
}

void LL_swap(List *list_p, Node *prev, Node *pos, int first_pos)
{
    printf("pos %s\n", pos->note.date);
    printf("prev %s\n", prev->note.date);
    printf("list_p %s\n", (*list_p)->note.date);
    printf("\n\n\n\nfirst item %s\n", (*list_p)->note.date);
    printf("second item %s\n", (*list_p)->next->note.date);
    printf("thrid item %s\n", (*list_p)->next->next->note.date);
    if ((*list_p)->next->next->next == NULL)
    {
        puts("4th item is NULL");
    }
    //  exit(1);
    if (first_pos == 0)
    {
        printf("mem loc of prev: %p, mem loc of pos: %p\n", prev, pos);
        printf("memloc of list_p: %p\n", *list_p);
        pos->next = *list_p;
        (*list_p)->next = LL_get_pos(list_p, first_pos + 2);

        //pos->next = tmp;
        // prev->next = LL_get_pos(list_p, first_pos + 2); // should be returning 22:12:2020
        printf("mem loc of prev: %p, mem loc of pos: %p\n", prev, pos);

        printf("first item %s\n", (*list_p)->note.date);
        printf("second item %s\n", (*list_p)->next->note.date);
        printf("thrid item %s\n", (*list_p)->next->next->note.date);
        // printf("4th item %s\n", (*list_p)->next->next->next);

        printf((prev->next)->note.date);
    }
    else
    {
        Node *wall_left = LL_get_pos(list_p, first_pos - 1);
        printf("left wall = %d, right wall = %d\n", first_pos - 1, first_pos + 2);
        wall_left->next = pos;
        pos->next = prev;
        prev->next = LL_get_pos(list_p, first_pos + 2);
    }
    printf("after swap");
}

int compare_dates(char *date1, char *date2)
{
    char piss1[5];
    char piss2[5];
    int num1, num2;

    if (strcmp(date1, date2) == 0)
    {
        puts("identical");
        return 0;
    }

    //year
    for (int i = 6; i < 11; i++)
    {
        piss1[i - 6] = date1[i];
        piss2[i - 6] = date2[i];
    }
    num1 = atoi(piss1);
    num2 = atoi(piss2);
    printf("%d, %d\n", num1, num2);

    if (num1 != num2)
    {
        if (atoi(piss1) > atoi(piss2))
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    //month
    int i = 3;
    for (; i < 5; i++)
    {
        piss1[i - 3] = date1[i];
        piss2[i - 3] = date2[i];
    }
    piss1[2] = '\0';
    piss2[2] = '\0';

    num1 = atoi(piss1);
    num2 = atoi(piss2);
    printf("%d, %d\n", num1, num2);

    if (num1 != num2)
    {
        if (atoi(piss1) > atoi(piss2))
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    //day
    for (int i = 0; i < 2; i++)
    {
        piss1[i] = date1[i];
        piss2[i] = date2[i];
    }
    num1 = atoi(piss1);
    num2 = atoi(piss2);
    printf("%d, %d\n", num1, num2);

    if (num1 != num2)
    {
        if (atoi(piss1) > atoi(piss2))
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
}

size_t LL_num(List *list_p)
{
    size_t count = (size_t)0;
    Node *tmp;
    for (tmp = *list_p; tmp != NULL; tmp = tmp->next)
    {
        printf("ayo");
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