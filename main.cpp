#include <stdio.h>

int slave(int);

int main(void)
{
    slave(56);
    while (true)
    {
        
    }
    
    return 0;
}

int slave(int number){
    printf("go slave");
    printf("your number is %d\n", number);
    return number;
}