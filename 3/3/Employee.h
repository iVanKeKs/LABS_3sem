//
// Created by ivankeks on 27.11.2019.
//

#ifndef LAB3_EMPLOYEE_H
#define LAB3_EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _employee Employee;

struct  _employee
{
    int id;
    char *name;
    char *surname;
    int pay;
};

// Убивает массив
void killMass(Employee **, int);

// Читает следующую запись в файле
int readNext(FILE*, Employee *);

#endif //LAB3_EMPLOYEE_H
