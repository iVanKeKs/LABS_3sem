//
// Created by iVan on 26.07.2020.
//

#ifndef INC_12_LIFOINT_H
#define INC_12_LIFOINT_H

#include <stdlib.h>

typedef struct _intLIFO IntLIFO;

struct _intLIFO
{
    int data;
    IntLIFO *next;
};

int	PopInt(IntLIFO **headLIFO);
void PushInt(IntLIFO **headLIFO, int data);
int	intLIFOSize(IntLIFO *head);

#endif //INC_12_LIFOINT_H
