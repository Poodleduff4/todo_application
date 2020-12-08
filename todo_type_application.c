#include "Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>

void menu(void);
int parse_file(FILE *);
void write_file(char *);
int add_item(void);

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
void add_list(int, Node *);
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

    if ((main_file = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Cannot open file");
        exit(EXIT_FAILURE);
    }

    head = (Node *)malloc(sizeof(Node));
    strcpy(head->note.data, "head");

    char menu_selection;

    while (1)
    {
        menu();
        scanf(" %c", &menu_selection);
        while (getchar() != '\n')
            ;

        switch (menu_selection)
        {
        case '1':
            parse_file(main_file);
            break;

        case '2':
            LL_print(&tmp_list);
            break;

        case '3':
            /* exiting  */
            fclose(main_file);
            write_file(argv[1]);
            LL_febreeze(&tmp_list);
            exit(EXIT_SUCCESS);
            /* TODO: run valgrind to check    */
            break;

        case '4':
            /* add item */
            add_item();
            break;

        case '5':;
            int pos;
            printf("delete which:");
            scanf("%d", &pos);
            LL_delete(pos, &tmp_list);
            break;

        default:
            break;
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
}

void menu(void)
{
    printf("Henlo, welcome to gay file reader.exe\n");
    printf("1. parse file\n2. output items\n3. exit\n4. add item\n5. delete item\nchoice: ");
}

int parse_file(FILE *file)
{
    char chars[MAX_LEN];
    while (fgets(chars, MAX_LEN, file) != NULL)
    {
        //printf("\ngay\n");
        /* remove newline from fgets    */
        LL_add(chars, &tmp_list);
        //printf("gay2\n");
        //LL_print(&tmp_list);
        // read_list();
        // add_list(-1, new);
        // read_list();
    }
    // LL_print(&tmp_list);
    printf("items parsed: %zd\n\n", LL_num(&tmp_list));
    //printf("out");
    return 0;
}

int add_item(void)
{
    char buf[MAX_LEN];
    fgets(buf, MAX_LEN, stdin);
    LL_add(buf, &tmp_list);
}

void write_file(char * name)
{
    Node *current = NULL;
    
    FILE * file = fopen(name, "w+"); /* check back on later? */
    
    if (file == NULL)
    {
        printf(" ");
    }

    for (current = tmp_list; current != NULL; current = current->next)
    {
        /* add header/tag/whatever 'note:'  */
        fprintf(file, "%s", current->note.data);
    }
}

/* notes:
Henlo, welcome to gay file reader.exe
1. read
2. write
3

*/

/* old code:

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
*/