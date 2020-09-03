//
// Created by iVan on 07.10.2019.
//

#include "Tasks.h"

//Замена в случайном массиве макс и мин эллементов

void swapElements(int *el1, int *el2)
{
    int buff = *el1;
    *el1 = *el2;
    *el2 = buff;
}


//Начало метода
void lab11()
{
    int mass[BUFSIZ];

    int *max = mass, *min = mass;

    srand(time(0));
    for(int i = 0; i<BUFSIZ; ++i)
    {
        mass[i] = rand() % 20;
        printf("%d ", mass[i]);
        if(mass[i] > *max)
        {
            max = mass+i;
        }
        else
        {
            if(mass[i] < *min)
            {
                min = mass+i;
            }
        }
    }

    printf("\nmax = %d\nmin = %d\n", *max, *min);
    swapElements(max, min);
    printf("max = %d\nmin = %d\n", *max, *min);
}