//
// Created by iVan on 16.08.2020.
//

#ifndef INC_2_MEMORYCELL_H
#define INC_2_MEMORYCELL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct __var Variable;
typedef struct __vararray ArrayOfVariables;

struct __var
{
    int	value;
    char *name;
};

struct __vararray
{
    int size;
    Variable *dataArray;
};

Variable *createVariable(char *nameOfNewVariable, int valueOfNewVariable, ArrayOfVariables *varArray);
void pushArray(char *inputString, ArrayOfVariables *varArray);
Variable *searchVariable(ArrayOfVariables *varArray, char *inputString);
void printVariables(char *inputString, ArrayOfVariables *varArray);
void freeArrayOfVariables(ArrayOfVariables *varArray);

void readFromFile(FILE *fileInput, char *buff);
void defineOperation(ArrayOfVariables *varArray, char *inputString);
void defineArguments(char *inputString, ArrayOfVariables *varArray, char operation);
int executeOperation(int leftValue, int rightValue, char operation, ArrayOfVariables *varArray);

#define ERROR_FILE_NOT_EXIST 1
#define ERROR_VARIABLE_NOT_EXIST ERROR_FILE_NOT_EXIST + 1
#define ERROR_DIVISION_BY_ZERO ERROR_VARIABLE_NOT_EXIST + 1
void error(int errorNumber, ArrayOfVariables *varArray);

int compareVariables(const Variable *leftVariable, const Variable *rightVariable);

#endif //INC_2_MEMORYCELL_H
