//
// Created by iVan on 27.08.2020.
//

#ifndef INC_8_HASHTABLE_H
#define INC_8_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 128

typedef struct __defineList list;

struct	__defineList
{
    char *nameOfDefine;
    char *value;
    list *next;

};

list *newList(char *nameOfDefine, char *valueOfDefine);
void freeArrayOfList(list **array);

void readFromFileAndParse(list **hashTable, FILE *fileInput);

#endif //INC_8_HASHTABLE_H
