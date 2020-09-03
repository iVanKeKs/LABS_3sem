//
// Created by iVan on 28.08.2020.
//

#include "BracketTree.h"

void readFromFile(FILE *fileInput, char *buff)
{
    char buffChar = '\0',
         *pbuff = buff;

    while(buffChar != '\n' && buffChar != EOF)
    {
        buffChar = fgetc(fileInput);

        if(!isspace(buffChar))
        {
            *pbuff++ = buffChar;
        }
    }

    *pbuff = '\0';
}

BracketTree *createNewNode(BracketTree *parentNode)
{
    BracketTree *newNode;

    newNode = (BracketTree*)malloc(sizeof(BracketTree));

    newNode->parent = parentNode;
    newNode->child.size = 0;

    return newNode;
}

void parseInputString(char *inputString, BracketTree **headTree)
{
    BracketTree *buffTree = *headTree;
    int levelOfBrackets = 0;

    while (*inputString != '\0')
    {
        if (isalpha(*inputString))
        {
            if (buffTree == NULL)
            {
                buffTree = createNewNode(NULL);

                buffTree->name = *inputString;
                ++inputString;
                continue;
            }
            
            buffTree->child.size++;
            if (buffTree->child.size == 1)
            {
                buffTree->child.nodes = malloc(sizeof(BracketTree));
            }
            else
            {
                buffTree->child.nodes = realloc(buffTree->child.nodes, sizeof(BracketTree) * buffTree->child.size);
            }

            buffTree->child.nodes[buffTree->child.size - 1] = createNewNode(buffTree);
            buffTree->child.nodes[buffTree->child.size - 1]->name = *inputString;
        }
        else if (*inputString == '(')
        {
            if (levelOfBrackets != 0)
            {
                buffTree = buffTree->child.nodes[buffTree->child.size - 1];
            }

            ++levelOfBrackets;
        }
        else if (*inputString == ')')
        {
            --levelOfBrackets;
            if (levelOfBrackets != 0)
            {
                buffTree = buffTree->parent;
            }
        }

        ++inputString;
    }

    *headTree = buffTree;
}

void printTree(BracketTree *currentNode, int treeDepth)
{
    for (int i = 0; i < treeDepth; i++)
    {
        printf(" ");
    }

    if(currentNode != NULL)
    {
        printf("%c\n", currentNode->name);

        for (int i = 0; i < currentNode->child.size; ++i)
        {
            printTree(currentNode->child.nodes[i], treeDepth + 1);
        }
    }
}

void freeTree(BracketTree *currentNode)
{
    for (int i = 0; i < currentNode->child.size; ++i)
    {
        freeTree(currentNode->child.nodes[i]);
        free(currentNode->child.nodes[i]);
    }

    if(currentNode->child.size != 0)
    {
        free(currentNode->child.nodes);
    }
}