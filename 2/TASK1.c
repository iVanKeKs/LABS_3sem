//
// Created by iVan on 28.09.2019.
//

#include "Tasks.h"

//Перезапис массива с числами на нечетных позициях

void RewritinhOdd(FILE *fileInput)
{
    int buff;
    int massOfTrueNumbers[64];

    int i = 0;
    int j = 1;
    while(!(feof(fileInput)))
    {
        if(j%2 != 0)
        {
            massOfTrueNumbers[i] = buff - '0';
            printf("%d ", buff);
            printf("j = %d ", j);
            ++i;
        }

        if(++j == 129)
        {
            printf("\nДальше массив читаться не будет\nПревышенно допустимое колличеество эллементов\n");
            return;
        }
    }
    printf("%d", j);
}