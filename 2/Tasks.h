//
// Created by iVan on 28.09.2019.
//

#ifndef LAB2_TASKS_H
#define LAB2_TASKS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

//   №1
void RewritinhOdd(FILE *fileInput);

//   №2
void RewritingEvenNumbers(FILE *fileInput);

//   №3
unsigned long mystrlenlul(const char *str);

//   №4
void ToUpperOdd(char *str);

//   №5
void SortingStr(char *str);

//   №6
void StringConcatenation(char *str1, char *str2);

//   №??
void labNonNumber(int n, ...);

//   №9
void lab9(char *str);

//   №10
void lab10(FILE* fileInput);

//   №11
void lab11();

//   №13 1
void lab13_1(int n, ...);

//   №13 2
void lab13_2(int n, ...);

//   №20
void lab20(int *matr1, int *matr2);

#endif //LAB2_TASKS_H
