//
// Created by iVan on 28.08.2020.
//

#ifndef INC_9_BRACKETTREE_H
#define INC_9_BRACKETTREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct __arrayOfChildNodes arrayOfNodes;
typedef struct __tree BracketTree;

struct __arrayOfChildNodes
{
    int	size;
    BracketTree **nodes;
};

struct __tree
{
    char name;
    BracketTree *parent;
    arrayOfNodes child;
};

BracketTree *createNewNode(BracketTree *parentNode);
void printTree(BracketTree *currentNode, int treeDepth);
void freeTree(BracketTree *currentNode);

void readFromFile(FILE *fileInput, char *buff);
void parseInputString(char *inputString, BracketTree **headTree);

#endif //INC_9_BRACKETTREE_H
