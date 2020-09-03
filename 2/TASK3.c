//
// Created by iVan on 29.09.2019.
//

#include "Tasks.h"

//Подсчет длины строки
unsigned long mystrlenlul(const char *str)
{
    unsigned long lenOfStr = 0;
    int i = 0;
    while(str[i++] != '\0')
    {
        ++lenOfStr;
    }

    return lenOfStr;
}