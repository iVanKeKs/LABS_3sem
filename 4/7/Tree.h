//
// Created by iVan on 25.08.2020.
//

#ifndef INC_7_TREE_H
#define INC_7_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

#define MAX(leftValue, rightValue) leftValue < rightValue ? rightValue : leftValue
#define TRUE 1

typedef struct __binaryTree BinaryTree;

struct __binaryTree
{
    char *nameOfVar;
    int data;
    BinaryTree *nextLeft;
    BinaryTree *nextRight;
};

BinaryTree* createNewNode(char *nameOfVar, int data);
BinaryTree *insertNewNode(BinaryTree *headTree, char *nameOfVar, int data);
BinaryTree* insertExistNode(BinaryTree *headTree, BinaryTree *newNode);

void printNode(BinaryTree *node, int position);
void printNodeInFile(BinaryTree *node, FILE *fileInput, char side);
void printTree(BinaryTree *headTree);

BinaryTree* searchByNameOfVar(BinaryTree *currentNode, const char *nameVar);
BinaryTree* createTreeFromTree(BinaryTree *sourceTree, BinaryTree *newTree);
int calculateDeepOfTree(BinaryTree *headTree);
void saveTree(BinaryTree *headTree, char *nameOfFile);
BinaryTree* loadTree(char *name);

void freeTree(BinaryTree *currentNode);

#endif //INC_7_TREE_H