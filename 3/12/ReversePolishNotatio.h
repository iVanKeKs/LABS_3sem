//
// Created by iVan on 10.07.2020.
//

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>

#include "LIFOchar.h"
#include "LIFOint.h"

#define BUFF_SIZE 100

void readToBuff(char *buff, FILE* fileInput);

int	operationPriority(char c);
int	NotationCalculation(char operation, IntLIFO **number);
void operation(char *operation, CharLIFO **operationLIFO, IntLIFO **numbersLIFO);
int	checkingForCorrectBracket(char *expression, CharLIFO **operationLIFO, IntLIFO **numbersLIFO);

int	ExpressionCalculation(char *inputExpression, int *result);

#endif
