//
// Created by iVan on 29.09.2019.
//

#include "Tasks.h"

void labNonNumber(int n, ...)
{
    va_list args;
    va_start(args, n);
    for(int i = 0; i < n; i++)
    {
        char* s = va_arg(args, char*);
        printf("%s\n", s);
    }

}