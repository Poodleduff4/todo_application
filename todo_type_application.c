#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

void menu(void);
int read_file(FILE *);
void write_file(FILE *);

/*
typedef struct item_st
{
    char data[MAX_LEN];

} Item;

typedef struct node_st2
{
    Item note;
    struct node_st2 *next;
} Node;
*/
void add_list(int, Node*);
void read_list();

Node *head = NULL;
List tmp_list;

int main(int argc, char *argv[])
{
    LL_init(&tmp_list);

    if (argc < 2)
    {
        fprintf(stderr, "filename not provided\n");
        exit(EXIT_FAILURE);
    }

    FILE *main_file;

    if ((main_file = fopen(argv[1], "r+")) == NULL)
    {
        fprintf(stderr, "Cannot open file");
        exit(EXIT_FAILURE);
    }

    head = (Node *) malloc(sizeof(Node));
    strcpy(head->note.data, "head");

    char menu_selection;
    menu();
    scanf(" %c", &menu_selection);

    switch (menu_selection)
    {
    case '1':
        read_file(main_file);
        break;

    default:
        break;

    case '2':
        write_file(main_file);
    }
    /*
    todo-application file.gay

        
            -> open file.gay
            -> 3 options:
                -> read
                -> write
                    -> timestamp
*/
}

void menu(void)
{
    printf("Henlo, welcome to gay file reader.exe\n");
    printf("1. read\n2. write\n");
}

int read_file(FILE *file)
{
    char chars[MAX_LEN];
    while (fgets(chars, MAX_LEN, file) != NULL)
    {
        printf("\ngay\n");
        LL_add(chars, &tmp_list);
        printf("gay2\n");
        Node * new = (Node* )malloc(sizeof(Node));
        printf("line: %s\n", chars);
        strcpy(new->note.data, chars);
        // read_list();
        add_list(-1, new);
        // read_list();
    }
    LL_print(&tmp_list);
    printf("out");
    return 0;
}

void add_list(int position, Node* add)
{
    printf("start add");
    Node *last = head;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = add;
    printf("end add");
}

void read_list()
{
    printf("read\n");
    Node *current = NULL;
    int i = 0;
    for (current = head; current != NULL; current = current->next, i++)
    {
        printf("%s  %d\n", current->note.data, i);
    }
    printf("done\n");
}

void write_file(FILE *file)
{

}

/* notes:
Henlo, welcome to gay file reader.exe
1. read
2. write
3

*/
