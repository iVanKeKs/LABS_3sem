//
// Created by iVan on 21.08.2020.
//

#include "TextParser.h"

Tree *createNewNode(char *inputString, int frequency)
{
    Tree *newNode;

    newNode = (Tree*)malloc(sizeof(Tree));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->frequency = frequency;
    newNode->data = (char*)malloc(sizeof(char) * (strlen(inputString) + 1));
    strcpy(newNode->data, inputString);

    return newNode;
}

void insertNewNode(Tree **headTree, char *inputString)
{
    if (*headTree == NULL)
    {
        *headTree = createNewNode(inputString, 1);
    }

    Tree *currentNode = *headTree;
    int resultOfCompare;
    while (currentNode != NULL)
    {
        resultOfCompare = strcmp(currentNode->data, inputString);
        if (resultOfCompare > 0)
        {
            if (currentNode->left != NULL)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode->left = createNewNode(inputString, 1);
                return ;
            }
        }
        else if (resultOfCompare < 0)
        {
            if (currentNode->right != NULL)
            {
                currentNode = currentNode->right;
            }
            else
            {
                currentNode->right = createNewNode(inputString, 1);
                return ;
            }
        }
        else if (resultOfCompare == 0)
        {
            currentNode->frequency++;
            return ;
        }
    }
}

void insertExistNode(Tree **headTree, char *word, int frequency)
{
    if (*headTree == NULL)
    {
        *headTree = createNewNode(word, frequency);
    }

    Tree *currentNode = *headTree;
    while(currentNode != NULL)
    {
        if (currentNode->frequency > frequency)
        {
            if (currentNode->left)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode->left = createNewNode(word, frequency);
                return ;
            }
        }
        else if (currentNode->frequency <= frequency)
        {
            if (currentNode->right)
            {
                currentNode = currentNode->right;
            }
            else
            {
                currentNode->right = createNewNode(word, frequency);
                return ;
            }
        }
    }
}

void searchLongNode(Tree *currentNode, char *longestString)
{
    if (currentNode == NULL)
    {
        return;
    }

    if (strlen(currentNode->data) > strlen(longestString))
    {
        strcpy(longestString, currentNode->data);
    }

    searchLongNode(currentNode->left, longestString);
    searchLongNode(currentNode->right, longestString);
}

void searchShortNode(Tree *currentNode, char *shortestString)
{
    if (currentNode == NULL)
    {
        return;
    }

    if (strlen(currentNode->data) < strlen(shortestString))
    {
        strcpy(shortestString, currentNode->data);
    }

    searchLongNode(currentNode->left, shortestString);
    searchLongNode(currentNode->right, shortestString);
}

int	calculateDeepOfTree(Tree *headTree)
{
    if (headTree == NULL)
    {
        return 0;
    }

    int maxDeep = MAX(calculateDeepOfTree(headTree->left), calculateDeepOfTree(headTree->right));

    return maxDeep + 1;
}

void recursiveSaveInFile(Tree *currentNode, FILE *fileOutput)
{
    if (currentNode == NULL)
    {
        return ;
    }

    fprintf(fileOutput, "%s %d %d %d\n", currentNode->data, currentNode->frequency, currentNode->left != NULL, currentNode->right != NULL);

    recursiveSaveInFile(currentNode->left, fileOutput);
    recursiveSaveInFile(currentNode->right, fileOutput);
}

void saveTree(Tree *headTree)
{
    FILE *fileInput;

    fileInput = fopen("save.txt", "w");

    recursiveSaveInFile(headTree, fileInput);

    fprintf(fileInput, "END\n");
    fclose(fileInput);
}

void swapTree(Tree *headTree, Tree **newTreeNode)
{
    if (headTree == NULL)
    {
        return;
    }

    insertExistNode(newTreeNode, headTree->data, headTree->frequency);

    swapTree(headTree->left, newTreeNode);
    swapTree(headTree->right, newTreeNode);

    free(headTree->data);
    free(headTree);
}

Tree *loadTree(Tree *headTree, FILE *fileInput)
{
    char buff[BUFSIZ];
    int frequency;
    int existLeftNode, existRightNode;

    fscanf(fileInput, "%s %d %d %d", buff, &frequency, &existLeftNode, &existRightNode);

    if (headTree == NULL)
    {
        headTree = createNewNode(buff, frequency);
    }

    if (existLeftNode == TRUE)
    {
        headTree->left = loadTree(headTree->left, fileInput);
    }

    if (existRightNode == TRUE)
    {
        headTree->right = loadTree(headTree->right, fileInput);
    }

    return headTree;
}

void printTree(Tree *headTree, int level)
{
    if (headTree == NULL)
    {
        return ;
    }

    for (int i = 0; i < level; ++i)
    {
        printf(" ");
    }

    printf("%s: %d\n", headTree->data, headTree->frequency);
    printTree(headTree->left, level + 1);
    printTree(headTree->right, level + 1);
}

void printLongestStrings(Tree *currentNode, int *numberOfStrings)
{
    if (currentNode == NULL)
    {
        return ;
    }

    printLongestStrings(currentNode->right, numberOfStrings);

    if (*numberOfStrings > 0)
    {
        printf("%s: %d\n", currentNode->data, currentNode->frequency);
        (*numberOfStrings)--;
    }

    printLongestStrings(currentNode->left, numberOfStrings);
}

void freeTree(Tree *currentNode)
{
    if (currentNode == NULL)
    {
        return ;
    }

    freeTree(currentNode->left);
    freeTree(currentNode->right);

    free(currentNode->data);
    free(currentNode);
}