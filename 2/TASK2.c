//
// Created by iVan on 29.09.2019.
//

#include "Tasks.h"

//Запись в массив только четных чисел

void RewritingEvenNumbers(FILE *fileInput)
{
    int massOfEvenNumbers[64];

    int i = -1;
    int j = 0;
    int buff;

    fscanf(fileInput, "%d", &buff);
    while(!(feof(fileInput)))
    {
        if(buff%2 == 0)
        {
            massOfEvenNumbers[++i] = buff;
            printf("%d ", buff);
        }

        if(++j == 129)
        {
            printf("\nДальше массив читаться не будет\nПревышенно допустимое колличеество эллементов\n");
            return;
        }
        fscanf(fileInput, "%d", &buff);
    }
    fclose(fileInput);
}