#include <stdio.h>

#include "Tasks.h"

int main(int argc, char **argv)
{
    int number;
    //scanf("%d", &number);
    if(argc == 1)
    {
        printf("Недостаточно операндов\n");
        exit(-1);
    }

    lab9();
    return 0;
}