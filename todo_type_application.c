#include "Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>

void menu(void);
int parse_file(FILE *);
void write_file(char *, FILE *);
void user_add_item(void);
char *nnlfget(char *, int, FILE *);

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

    char menu_selection;

    while (1)
    {
        menu();
        scanf(" %c", &menu_selection);
        while (getchar() != '\n')
            ;
        putchar('\n');

        switch (menu_selection)
        {
        case 'p':
            parse_file(main_file);
            break;

        case 'l':
            LL_print(&tmp_list);
            break;

        case 'a':
            /* add item */
            user_add_item();
            break;

        case 'd':;
            int pos;
            printf("delete which:");
            scanf("%d", &pos);
            LL_delete(pos, &tmp_list);
            break;

        case 's':;
            /* sort items -- start with sorting the date (numerical is easier)  */
            /* not sorting in place as that would lose the original order of the linked list    */
            // LL_sort_date(&tmp_list);
            // LL_print(&tmp_list);
            //printf("tmp list date = %s\n", tmp_list->note.date);
            //printf("tmp_list->next date = %s\n", tmp_list->next->note.date);
            //printf("tmp_list->next->next date = %s\n", tmp_list->next->next->note.date);
            LL_swap(&tmp_list, tmp_list, tmp_list->next, 0);
            break;

        case 'e':
            /* exiting  */
            write_file(argv[1], main_file);
            fclose(main_file);
            LL_febreeze(&tmp_list);
            exit(EXIT_SUCCESS);
            /* TODO: run valgrind to check    */
            break;

        default:
            break;
        }
    }
}

void menu(void)
{
    printf("\nHenlo, welcome to gay file reader.exe\n");
    printf("p: (p)arse file       l: (l)ist items       a: (a)dd item       d: (d)elete item       s: (s)ort by date       e: (e)xit\nChoice: ");
}

int parse_file(FILE *file)
{
    char chars[MAX_LEN]; /* tmp buffer  */

    char note[MAX_LEN];
    char tag[MAX_TAG_LEN];
    char date[MAX_DATE];
    int count = LL_num(&tmp_list);
    while (nnlfget(chars, MAX_LEN, file) != NULL)
    {
        if (strcmp(chars, "ITEM") == 0) // maybe don't need
        {
            puts("new item");
            if (nnlfget(chars, MAX_LEN, file) != NULL)
            {
                strcpy(note, chars);
            }

            if (nnlfget(chars, MAX_TAG_LEN, file) != NULL)
            {
                strcpy(tag, chars);
            }
            puts("before date");
            if (nnlfget(chars, MAX_DATE, file) != NULL)
            {
                strcpy(date, chars);
            }
            puts("After date");

            if (strcmp(nnlfget(chars, MAX_LEN, file), "ENDITEM") != 0)
            {
                fprintf(stderr, "dsomritng");
            }
            puts("after end");
        }
        LL_add(note, tag, date, &tmp_list);
    }
    printf("items parsed: %zd\n\n", LL_num(&tmp_list) - count);
    return 0;
}

void user_add_item(void)
{
    char buf[MAX_LEN];
    char data[MAX_LEN];
    char tag[MAX_TAG_LEN];
    char date[MAX_DATE];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    printf("enter the data:");
    if (nnlfget(buf, MAX_LEN, stdin) == NULL)
    {
        fprintf(stderr, "something went wrong with adding that string");
        return; /* treat as fatal   */
    }
    strcpy(data, buf);

    printf("enter the tag (enter for none):");
    if (nnlfget(buf, MAX_LEN, stdin) == NULL || *buf == '\n')
    {
        strcpy(tag, "none");
    }
    else
    {
        strcpy(tag, buf);
    }

    if (tm->tm_mon < 10)
    {
        sprintf(date, "%d:0%d:%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    }
    else
    {
        sprintf(date, "%d:%d:%d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    }

    LL_add(data, tag, date, &tmp_list);
}

char *nnlfget(char *str, int up_to, FILE *input_stream)
{
    char *tmp = fgets(str, up_to, input_stream);
    int index = 0;

    if (tmp) /* not NULL (read something)    */
    {
        while (str[index] != '\n' && str[index] != '\0') /* find the end of input (either newline or null character) */
        {
            index++;
        }
        if (str[index] == '\n') /* if the whole input was read (meaning that there is a newline at the end) */
        {
            str[index] = '\0'; /* get rid of newline   */
        }
        else
        {
            char c = fgetc(input_stream);
            while (c != '\n' && c != EOF) /* some input was skipped so read the rest of the input in the buffer   */
            {
                c = fgetc(input_stream);
            }
        }
    }
    return tmp;
}

void write_file(char *name, FILE *main_file)
{
    Node *current = NULL;

    FILE *file = freopen(name, "w+", main_file); /* check back on later? */

    if (file == NULL)
    {
        printf("problem with file ");
    }

    for (current = tmp_list; current != NULL; current = current->next)
    {
        fprintf(file, "ITEM\n");
        fprintf(file, "%s\n%s\n%s\n", current->note.data, current->note.tag, current->note.date);
        fprintf(file, "ENDITEM\n");
    }
}