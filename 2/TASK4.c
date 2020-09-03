//
// Created by iVan on 29.09.2019.
//

//Преобразование в верхний регистр нечетных литер

#include <ctype.h>

#include "Tasks.h"

void ToUpperOdd(char *str)
{
    int i = -1;

    while(str[++i] != '\0')
    {
        if(i%2 == 0)
        {
            str[i] = toupper(str[i]);
        }
    }
}