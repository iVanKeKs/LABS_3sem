//
// Created by iVan on 21.08.2020.
//

#ifndef INC_5_TEXTPARSER_H
#define INC_5_TEXTPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX(leftValue, rightValue) leftValue > rightValue ? leftValue : rightValue

#define LENGTH_WITHOUT_FILE 1
#define TRUE 1

typedef struct __binaryTree Tree;
typedef struct __string StrWithLen;

struct __string
{
    int length;
    char *data;
};

struct	__binaryTree
{
    Tree *left;
    Tree *right;

    char *data;
    int frequency;
};

Tree *createNewNode(char *inputString, int frequency);
void insertNewNode(Tree **headTree, char *inputString);
void insertExistNode(Tree **headTree, char *word, int frequency);
void freeTree(Tree *currentNode);

void searchShortNode(Tree *currentNode, char *shortestString);
void searchLongNode(Tree *currentNode, char *longestString);

int	calculateDeepOfTree(Tree *headTree);
void saveTree(Tree *headTree);
Tree *loadTree(Tree *headTree, FILE *fileInput);
void swapTree(Tree *headTree, Tree **newTreeNode);

void printLongestStrings(Tree *currentNode, int *numberOfStrings);
void printTree(Tree *headTree, int level);


#endif //INC_5_TEXTPARSER_H
