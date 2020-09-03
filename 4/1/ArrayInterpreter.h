//
// Created by iVan on 11.08.2020.
//

#ifndef INC_1_ARRAYINTERPRETER_H
#define INC_1_ARRAYINTERPRETER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "TechnicalMetods.h"

#define NUMBER_OF_OPERATION 11
#define MAX(a, b) a > b ? a : b

typedef struct __array Array;

struct __array
{
    int size;
    int *data;
};

void readFromFile(FILE *, char *);

void searchAndExeOperation(char *);

void loadArrayFromFile(char *);
void saveArrayToFile(char *);

void concatenationArray(char *);
void randomizeArray(char *);

void freeArray(char *);
void removeElementsFromArray(char *);

void copyArray(char *);
void sortArray(char *);
void permuteArray(char *);
void informationAboutArray(char *);

void printArray(char *);

void(*arrayOfFunctionPointers[NUMBER_OF_OPERATION])(char *);
char *arrayOfFunctionNames[NUMBER_OF_OPERATION];

#endif //INC_1_ARRAYINTERPRETER_H
