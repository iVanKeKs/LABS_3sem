//
// Created by iVan on 28.08.2020.
//

#ifndef INC_10_ARITHMETICBINARYTREE_H
#define INC_10_ARITHMETICBINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

typedef struct __bTree BinaryTree;
typedef struct __LIFOTRee LIFOTree;
typedef struct __LIFOOnArray LIFO;

#define SIZE_OF_ALPHABET 26

struct	__bTree
{
    char value;
    int isNegative;

    BinaryTree *left;
    BinaryTree *right;

};

struct	__LIFOTRee
{
    BinaryTree *tree;
    LIFOTree *next;
};

struct __LIFOOnArray
{
    char data[BUFSIZ];
    int size;
};

void CalculateBinaryExpression(FILE *fileInput);

#endif //INC_10_ARITHMETICBINARYTREE_H
