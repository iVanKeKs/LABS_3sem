//
// Created by iVan on 25.08.2020.
//

#include "Tree.h"

BinaryTree* createNewNode(char* nameOfVar, int data)
{
    BinaryTree* newNode = NULL;

    newNode = (BinaryTree*)malloc(sizeof(BinaryTree));

    newNode->nameOfVar = (char*)malloc(strlen(nameOfVar) + 1);
    strcpy(newNode->nameOfVar, nameOfVar);
    newNode->data = data;

    newNode->nextLeft = NULL;
    newNode->nextRight = NULL;

    return newNode;
}

void printNode(BinaryTree* node, int position)
{
    if (node == NULL)
    {
        return;
    }

    for(int i = 0; i < position; ++i)
    {
        printf(" ");
    }

    printf("%s = %d\n", node->nameOfVar, node->data);
}

void printNodeInFile(BinaryTree* node, FILE *fileInput, char side)
{
    if (node == NULL)
    {
        return;
    }

    fprintf(fileInput, "%s = %d %c\n", node->nameOfVar, node->data, side);
}

void printTree(BinaryTree* headTree)
{
    if (headTree == NULL)
    {
        return;
    }

    static int deep = 0;
    printNode(headTree, deep);
    ++deep;
    printTree(headTree->nextLeft);
    printTree(headTree->nextRight);
}

BinaryTree* searchByNameOfVar(BinaryTree* currentNode, const char* nameVar)
{
    if (currentNode == NULL)
    {
        return NULL;
    }

    int resultOfCompare = strcmp(currentNode->nameOfVar, nameVar);

    if (resultOfCompare == 0)
    {
        return currentNode;
    }
    else if (resultOfCompare > 0)
    {
        return searchByNameOfVar(currentNode->nextLeft, nameVar);
    }
    else
    {
        return searchByNameOfVar(currentNode->nextRight, nameVar);
    }
}

void recursiveInsertion(BinaryTree *currentNode, BinaryTree *newNode)
{
    int resultOfCompare = strcmp(currentNode->nameOfVar, newNode->nameOfVar);

    if (resultOfCompare == 0)
    {
        return;
    }
    else if (resultOfCompare > 0)
    {
        if (currentNode->nextLeft == NULL)
        {
            currentNode->nextLeft = newNode;
            return;
        }
        else
        {
            recursiveInsertion(currentNode->nextLeft, newNode);
        }
    }
    else
    {
        if (currentNode->nextRight == NULL)
        {
            currentNode->nextRight = newNode;
            return;
        }
        else
        {
            recursiveInsertion(currentNode->nextRight, newNode);
        }
    }
}

BinaryTree *insertExistNode(BinaryTree *headTree, BinaryTree *newNode)
{
    if (headTree == NULL)
    {
        return newNode;
    }
    else
    {
        recursiveInsertion(headTree, newNode);
        return headTree;
    }
}

BinaryTree *insertNewNode(BinaryTree *headTree, char *nameOfVar, int data)
{
    if (headTree == NULL)
    {
        return createNewNode(nameOfVar, data);
    }
    else
    {
        recursiveInsertion(headTree, createNewNode(nameOfVar, data));
        return headTree;
    }
}

BinaryTree* createTreeFromTree(BinaryTree* sourceTree, BinaryTree* newTree)
{
    if (sourceTree == NULL)
    {
        return NULL;
    }

    newTree = insertExistNode(newTree, createNewNode(sourceTree->nameOfVar, sourceTree->data));

    newTree = createTreeFromTree(sourceTree->nextLeft, newTree);
    newTree = createTreeFromTree(sourceTree->nextRight, newTree);

    return newTree;
}

int calculateDeepOfTree(BinaryTree* headTree/*, int n = 0*/)
{
    if (headTree == NULL)
    {
        return 0;
    }

    int maxDeep = MAX(calculateDeepOfTree(headTree->nextLeft), calculateDeepOfTree(headTree->nextRight));

    return maxDeep + 1;
}

void recursiveSaveInFile(BinaryTree* currentNode, FILE* fileOutput)
{
    if (currentNode == NULL)
    {
        return ;
    }

    fprintf(fileOutput, "%s %d %d %d\n", currentNode->nameOfVar, currentNode->data, currentNode->nextLeft != NULL, currentNode->nextRight != NULL);

    recursiveSaveInFile(currentNode->nextLeft, fileOutput);
    recursiveSaveInFile(currentNode->nextRight, fileOutput);
}

void saveTree(BinaryTree *headTree, char* nameOfFile)
{
    FILE *fileOutput;
    fileOutput = fopen(nameOfFile, "w");

    recursiveSaveInFile(headTree, fileOutput);

    fprintf(fileOutput, "END\n");
    fclose(fileOutput);
}

BinaryTree *recursiveLoadTreeFromFile(BinaryTree *currentNode, FILE *fileInput)
{
    char buff[BUFSIZ];
    int data;
    int existLeftNode,
        existRightNode;

    fscanf(fileInput, "%s %d %d %d", buff, &data, &existLeftNode, &existRightNode);

    if (currentNode == NULL)
    {
        currentNode = createNewNode(buff, data);
    }

    if (existLeftNode == TRUE)
    {
        currentNode->nextLeft = recursiveLoadTreeFromFile(currentNode->nextLeft, fileInput);
    }

    if (existRightNode == TRUE)
    {
        currentNode->nextRight = recursiveLoadTreeFromFile(currentNode->nextRight, fileInput);
    }

    return currentNode;
}

BinaryTree *loadTree(char *nameOfFile)
{
    FILE *fileInput = fopen(nameOfFile, "w");

    BinaryTree *newTree = NULL;

    newTree = recursiveLoadTreeFromFile(newTree, fileInput);
    return newTree;
}

void freeTree(BinaryTree* currentNode)
{
    if (currentNode == NULL)
    {
        return;
    }

    freeTree(currentNode->nextLeft);
    freeTree(currentNode->nextRight);

    free(currentNode->nameOfVar);
    free(currentNode);
}