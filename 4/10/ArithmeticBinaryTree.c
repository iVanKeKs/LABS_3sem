//
// Created by iVan on 28.08.2020.
//

#include "ArithmeticBinaryTree.h"

LIFOTree *headOfLIFOTree;

BinaryTree *createNewTree(char newValue, int isNegative)
{
    BinaryTree *newNode = (BinaryTree*)malloc(sizeof(BinaryTree));

    newNode->value = newValue;
    newNode->isNegative = isNegative;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


BinaryTree *createNewNodeWithChildren(char newValue, BinaryTree *leftNode, BinaryTree *rightNode)
{
    BinaryTree *tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->value = newValue;
    tree->isNegative = 0;

    tree->left = leftNode;
    tree->right = rightNode;

    return tree;
}

void pushOnLIFOTree(BinaryTree *tree)
{
    LIFOTree *newNode = malloc(sizeof(LIFOTree));

    newNode->next = headOfLIFOTree;
    newNode->tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    newNode->tree = tree;
    headOfLIFOTree = newNode;
}

BinaryTree *popFromLIFOTree()
{
    LIFOTree *buff = headOfLIFOTree;
    BinaryTree *outputTree = (headOfLIFOTree)->tree;

    headOfLIFOTree = headOfLIFOTree->next;
    free(buff);

    return outputTree;
}

BinaryTree *peekOnLIFOTree()
{
    if (headOfLIFOTree == NULL)
    {
        return NULL;
    }

    return headOfLIFOTree->tree;
}

void printTree(BinaryTree *headTree, int deep)
{
    if(headTree == NULL)
    {
        return;
    }

    printTree(headTree->left, deep + 1);

    for (int i = 0; i < deep; i++)
    {
        printf("\t");
    }

    if (headTree->isNegative)
    {
        printf("~");
    }

    printf("%c", headTree->value);

    if (headTree->value == '<' || headTree->value == '+' || headTree->value == '-')
    {
        printf(">");
    }

    printf("\n");

    printTree(headTree->right, deep + 1);
}

void pushOnLIFO(LIFO *headLIFO, char inputVariable)
{
    headLIFO->data[headLIFO->size] = inputVariable;
    headLIFO->size++;
}

char popFromLIFO(LIFO *headLIFO)
{
    if (headLIFO->size == 0)
    {
        return NULL;
    }

    headLIFO->size--;
    return headLIFO->data[headLIFO->size];
}

char peekOnLIFO(LIFO *headLIFO)
{
    return headLIFO->data[headLIFO->size - 1];
}

void treeToLIFO(BinaryTree *currentNode, int i, char *arrayOfLetters, LIFO *stack)
{
    if(currentNode == NULL)
    {
        return;
    }

    int j;

    treeToLIFO(currentNode->right, i, arrayOfLetters, stack);
    treeToLIFO(currentNode->left, i, arrayOfLetters, stack);

    if (isalpha(currentNode->value))
    {
        for(j = 0; j < strlen(arrayOfLetters); j++)
        {
            if(currentNode->value == arrayOfLetters[j])
            {
                break;
            }
        }
        pushOnLIFO(stack, (i >> j & 1) + '0');
    }
    else
    {
        pushOnLIFO(stack, currentNode->value);
    }
}

void createSupposedValues(int *array, int numberOfString, int numberOfLetters, char *arrayOfVariables)
{
    for (int i = 0; i < numberOfLetters; i++)
    {
        array[tolower(*arrayOfVariables) - 'a'] = (numberOfString >> i) & 1;
        printf("%d", (numberOfString >> i) & 1);
        arrayOfVariables++;
    }
}

int calculate(int leftNode, int rightNode, char operation)
{
    switch (operation)
    {
        case('|'):
        {
            return leftNode | rightNode;
        }
        case('-'):
        {
            return !(leftNode) | rightNode;
        }
        case('<'):
        {
            return !(leftNode == rightNode);
        }
        case ('='):
        {
            return leftNode == rightNode;
        }
        case('&'):
        {
            return leftNode & rightNode;
        }
        case('+'):
        {
            return leftNode & (!rightNode);
        }
        case('!'):
        {
            return !(leftNode & rightNode);
        }
        case('?'):
        {
            return !(leftNode | rightNode);
        }
        case('~'):
        {
            return !leftNode;
        }
    }
}

int	calculateTree(int *array, BinaryTree *headTree)
{
    if (isalpha(headTree->value))
    {
        return array[headTree->value - 'a'];
    }

    return calculate(calculateTree(array, headTree->left), calculateTree(array, headTree->right), headTree->value);
}

int priorityOfOperation(char operation)
{
    if (operation == '~')
    {
        return 3;
    }
    else if (operation == '?' || operation == '!' || operation == '+' || operation == '&')
    {
        return 2;
    }
    else if (operation == '|' || operation == '-' || operation == '<' || operation == '=')
    {
        return 1;
    }
}

void CalculateBinaryExpression(FILE *fileInput)
{
    LIFO headLIFO;
    headLIFO.size = 0;

    int numberOfLetter = 0;

    char buffChar,
         arrayOfVariable[SIZE_OF_ALPHABET];

    int isNegative;

    while(!feof(fileInput))
    {
        buffChar = fgetc(fileInput);
        if(buffChar == EOF || buffChar == '\n')
        {
            continue;
        }

        isNegative = 0;

        if (buffChar == '~')
        {
            buffChar = fgetc(fileInput);
            isNegative = 1;
        }

        if (buffChar == '<' || buffChar == '+' || buffChar == '-')
        {
            if(fgetc(fileInput) != '>')
            {
                exit(-1);
            }
        }

        if (isalpha(buffChar) || buffChar == '1' || buffChar == '0')
        {
            if (isalpha(buffChar) && strstr(arrayOfVariable, &buffChar) == NULL)
            {
                arrayOfVariable[numberOfLetter++] = buffChar;
            }

            pushOnLIFOTree(createNewTree(buffChar, isNegative));
        }
        else if (buffChar != ')' &&
                 (headLIFO.size == 0 || priorityOfOperation(buffChar) > priorityOfOperation(peekOnLIFO(&headLIFO))
                  || buffChar == '(' || peekOnLIFO(&headLIFO) == '('))
        {
            pushOnLIFO(&headLIFO, buffChar);
        }
        else
        {
            while(headLIFO.size != 0 && ((buffChar == ')' && peekOnLIFO(&headLIFO) != '(') ||
                                         priorityOfOperation(peekOnLIFO(&headLIFO)) >= priorityOfOperation(buffChar)))
            {
                BinaryTree *new = createNewNodeWithChildren(popFromLIFO(&headLIFO), popFromLIFOTree(),
                                                            popFromLIFOTree());
                pushOnLIFOTree(new);
            }
            if (peekOnLIFO(&headLIFO) == '(' && buffChar == ')')
            {
                popFromLIFO(&headLIFO);
            }
            if (buffChar != ')')
            {
                pushOnLIFO(&headLIFO, buffChar);
            }
        }
    }

    while(headLIFO.size != 0)
    {
        BinaryTree *new = createNewNodeWithChildren(popFromLIFO(&headLIFO), popFromLIFOTree(), popFromLIFOTree());
        pushOnLIFOTree(new);
    }

    printTree(peekOnLIFOTree(), 0);

    int arrayOfSupposedValues[26],
        quantityOfStrings = pow(2, numberOfLetter);

    printf("\t%s = F\n", arrayOfVariable);

    for (int numberOfString = 0; numberOfString < quantityOfStrings; ++numberOfString)
    {
        printf("%d:\t", numberOfString+1);
        createSupposedValues(arrayOfSupposedValues, numberOfString, numberOfLetter, arrayOfVariable);
        printf (" = %d\n", calculateTree(arrayOfSupposedValues, peekOnLIFOTree()));
    }
}
