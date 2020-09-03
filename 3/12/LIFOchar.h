//
// Created by iVan on 26.07.2020.
//

#ifndef INC_12_LIFOCHAR_H
#define INC_12_LIFOCHAR_H

#include <stdlib.h>

typedef struct _charLIFO CharLIFO;

struct _charLIFO
{
    char data;
    CharLIFO *next;
};

char PopChar(CharLIFO **headLIFO);
void PushChar(CharLIFO **headLIFO, char letter);

#endif //INC_12_LIFOCHAR_H
