//
// Created by ivankeks on 29.11.2019.
//

#ifndef LAB3_STUDENTS_H
#define LAB3_STUDENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct _students Students;

struct _students
{
    int id;
    char name[256];
    char surname[256];
    char group[256];
};

// Убивает массив
void killMassOfStudents(Students **, int);

// Читает следующую запись в файле
int readNextOfStudents(FILE*, Students *);

Students *searchById(char *, Students **, int);
Students **searchByName(char *, Students **, int);
Students **searchBySurname(char *, Students **, int);
Students **searchByGroup(char *, Students **, int);

#endif //LAB3_STUDENTS_H
