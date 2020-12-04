#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void);
int read_file(FILE *);
int write_file(FILE *);

struct Node
{
    char data[100];
    struct Node *next;
};

void add_list(int, char[]);
void read_list();
void printList();
struct Node *head = NULL;
int main(int argc, char *argv[])
{
    head = (struct Node *)malloc(sizeof(struct Node));
    strcpy(head->data, "head");
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
    char chars[100];
    fscanf(file, "%[^\n]", chars);
    printf("Data from the file:\n%s\n", chars);
    printf("chars: %s\n", chars);
    read_list();
    add_list(-1, chars);
    printList(head);
    printf("gay\n");
}

int write_file(FILE *file)
{
}

void add_list(int position, char data[100])
{
    struct Node *add = NULL;
    add = (struct Node *)malloc(sizeof(struct Node));
    strcpy(add->data, data);
    printf("add\n");
    struct Node *last = head;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = add;
    
}

void read_list()
{
    printf("read\n");
    struct Node *current = NULL;
    int i = 0;
    for (current = head; current != NULL; current = current->next, i++)
    {
        printf("%s  %d\n", current, i);
    }
    printf("done");
}

void printList() 
{ 
    struct Node* n = head;
    while (n != NULL) { 
        printf("%s\n", n->data); 
        n = n->next; 
    } 
    printf("done");
} 

/* notes:
Henlo, welcome to gay file reader.exe
1. read
2. write
3

*/
