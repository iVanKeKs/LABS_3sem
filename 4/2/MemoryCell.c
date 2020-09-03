//
// Created by iVan on 16.08.2020.
//

#include "MemoryCell.h"

void readFromFile(FILE *fileInput, char *buff)
{
    char buffChar,
         *pbuff = buff;

    while((buffChar = getc(fileInput)) != ';')
    {
        if(isspace(buffChar))
        {
            if(buffChar != '\n' && buffChar != '\r')
            {
                *pbuff++ = ' ';
            }
            while(isspace(buffChar))
            {
                buffChar = getc(fileInput);
            }
        }

        *pbuff++ = tolower(buffChar);
    }

    *pbuff = '\0';
}

Variable *searchVariable(ArrayOfVariables *varArray, char *inputString)
{
    int leftBound = 0;
    int rightBound = varArray->size - 1;
    int middle = 0;

    while(1)
    {
        middle = (leftBound + rightBound) / 2;

        if (strcmp(varArray->dataArray[middle].name, inputString) > 0)
        {
            rightBound = middle - 1;
        }
        else if (strcmp(varArray->dataArray[middle].name, inputString) < 0)
        {
            leftBound = middle + 1;
        }
        else
        {
            return varArray->dataArray + middle;
        }

        if (leftBound > rightBound)
        {
            return NULL;
        }
    }
}

void printVariables(char *inputString, ArrayOfVariables *varArray)
{
    if(varArray->size == 0)
    {
        return;
    }

    if (strlen(inputString) == 5)
    {
        for (int i = 0; i < varArray->size; i++)
        {
            printf("%s = %d\n", varArray->dataArray[i].name, varArray->dataArray[i].value);
        }
    }
    else
    {
        Variable *buffVariable;

        inputString = strchr(inputString, ' ') + 1;

        if((buffVariable = searchVariable(varArray, inputString)) == NULL)
        {
            error(ERROR_VARIABLE_NOT_EXIST, varArray);
        }

        printf("%s = %d\n", buffVariable->name, buffVariable->value);
    }
}

int executeOperation(int leftValue, int rightValue, char operation, ArrayOfVariables *varArray)
{
    switch (operation)
    {
        case('+'):
        {
            return leftValue + rightValue;
        }
        case('-'):
        {
            return leftValue - rightValue;
        }
        case('/'):
        {
            if (rightValue == 0)
            {
                error(ERROR_DIVISION_BY_ZERO, varArray);
            }

            return leftValue / rightValue;
        }
        case('*'):
        {
            return leftValue * rightValue;
        }
        case('%'):
        {
            if (rightValue == 0)
            {
                error(ERROR_DIVISION_BY_ZERO, varArray);
            }

            return leftValue % rightValue;
        }
    }
}

Variable *createVariable(char *nameOfNewVariable, int valueOfNewVariable, ArrayOfVariables *varArray)
{
    Variable *newVariable;

    varArray->size++;

    if (varArray->size == 1)
    {
        varArray->dataArray = (Variable*)malloc(sizeof(Variable));
    }
    else
    {
        varArray->dataArray = (Variable*)realloc(varArray->dataArray, sizeof(Variable) * varArray->size);
    }

    newVariable = varArray->dataArray + varArray->size - 1;
    newVariable->name = (char*)malloc(sizeof(char) * (strlen(nameOfNewVariable) + 1));

    strcpy(newVariable->name, nameOfNewVariable);
    newVariable->value = valueOfNewVariable;

    qsort(varArray->dataArray, varArray->size, sizeof(varArray->dataArray[0]),
          (int (*)(const void *, const void *)) compareVariables);
    return searchVariable(varArray, nameOfNewVariable);
}

void defineArguments(char *inputString, ArrayOfVariables *varArray, char operation)
{
    char *resultVariableName,
         *leftVariableName,
         *rightVariableName;

    Variable *resultVariable,
             *leftVariable,
             *rightVariable;

    resultVariableName = inputString;

    leftVariableName = strchr(inputString, '=');
    *leftVariableName++ = '\0';

    if ((resultVariable = searchVariable(varArray, resultVariableName)) == NULL)
    {
        resultVariable = createVariable(resultVariableName, 0, varArray);
    }

    rightVariableName = strchr(leftVariableName, operation);
    *rightVariableName++ = '\0';

    if ((leftVariable = searchVariable(varArray, leftVariableName)) == NULL)
    {
        error(ERROR_VARIABLE_NOT_EXIST, varArray);
    }

    if ((rightVariable = searchVariable(varArray, rightVariableName)) == NULL)
    {
        error(ERROR_VARIABLE_NOT_EXIST, varArray);
    }

    resultVariable->value = executeOperation(leftVariable->value, rightVariable->value, operation, varArray);
}

void pushArray(char *inputString, ArrayOfVariables *varArray)
{
    char *pstr = inputString;
    int variableValue;

    pstr = strchr(pstr, '=');
    *pstr++ = '\0';

    variableValue = atoi(pstr);
    createVariable(inputString, variableValue, varArray);
}

void defineOperation(ArrayOfVariables *varArray, char *inputString)
{
    if(strstr(inputString, "print"))
    {
        printVariables(inputString, varArray);
        return ;
    }

    if(strchr(inputString, '+'))
    {
        defineArguments(inputString, varArray, '+');
    }
    else if(strchr(inputString, '-'))
    {
        defineArguments(inputString, varArray, '-');
    }
    else if(strchr(inputString, '*'))
    {
        defineArguments(inputString, varArray, '*');
    }
    else if(strchr(inputString, '/'))
    {
        defineArguments(inputString, varArray, '/');
    }
    else if(strchr(inputString, '%'))
    {
        defineArguments(inputString, varArray, '%');
    }
    else
    {
        pushArray(inputString, varArray);
    }
}

void freeArrayOfVariables(ArrayOfVariables *varArray)
{
    if(varArray == NULL)
    {
        return;
    }

    for (int i = 0; i < varArray->size; i++)
    {
        free(varArray->dataArray[i].name);
    }

    free(varArray->dataArray);
}


char *errors[] = {"Файл не существует",
                  "Переменной не существует",
                  "Деление на ноль"};

void error(int errorNumber, ArrayOfVariables *varArray)
{
    printf("Error: %s", errors[errorNumber-1]);

    freeArrayOfVariables(varArray);
    exit(errorNumber);
}

int compareVariables(const Variable *leftVariable, const Variable *rightVariable)
{
    return strcmp(leftVariable->name, rightVariable->name);
}