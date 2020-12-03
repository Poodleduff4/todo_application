#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void);
int read_file(FILE *);
int write_file(FILE *);

int main(int argc, char *argv[])
{
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

int read_file(FILE* file)
{
    char line[100];
    fscanf(file, "%[^\n]", line);
    printf("Data from the file:\n%s", line);
}

int write_file(FILE* file)
{

}

/* notes:
Henlo, welcome to gay file reader.exe
1. read
2. write
3

*/
