#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>

#include "Tasks.h"


int main(int argv, char** argc)
{
    FILE *fin;

    if(argv == 1)
    {
        printf("");
        exit(-1);
    }

    if(!(fin = fopen(argc[1], "r")))
    {
        printf("Не удалось открыть файл для чтения");
        exit(-1);
    }

    char str1[] = "1234567890",
         str2[] = "11111111111111111111111";

    double x1 = 1, x2 = 1, x3 = 2, x4 = 2,
           y1 = 2, y2 = 1, y3 = 1, y4 = 2;

    lab13_2(4, x1, y1, x2, y2, x3, y3, x4, y4);

    //printf("%s", str1);
    fclose(fin);
    return 0;
}