//
// Created by iVan on 05.10.2019.
//

#include "Tasks.h"

//Реверс строки

void lab9(char *str)
{
    unsigned long sizeMass = strlen(str);

    char buff;
    char *startOfStr = str,              //Указатель на начало строки
         *endOfStr = &str[sizeMass-1];   //Указатель на конец строки

    while(startOfStr < endOfStr)
    {
        buff = *startOfStr;
        *startOfStr++ = *endOfStr;
        *endOfStr-- = buff;
    }
}