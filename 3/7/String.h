//
// Created by ivankeks on 02.12.2019.
//

#ifndef LAB3_STRING_H
#define LAB3_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __string String;

struct __string
{
    unsigned int sizeOfString;
    char *data;
};


// Создание строки
String *creatString(char *);


// Удаление строки
void killString(String *);


// Сравнение строк
unsigned int cmpStrings(String *, String *);


// Конкатенация строк
int cntStrings(String *, String *);


// Дублирование строк
String *copyString(String *);


#endif //LAB3_STRING_H
