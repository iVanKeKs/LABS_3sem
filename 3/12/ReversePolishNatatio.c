//
// Created by iVan on 10.07.2020.
//

#include "ReversePolishNotatio.h"
#include <stdio.h>
#include <math.h>
#include <ctype.h>

void readToBuff(char *buff, FILE* fileInput)
{
    char letterBuff = fgetc(fileInput),
         *pbuff = buff;

    while(letterBuff != '\n' && !feof(fileInput))
    {
        if(isgraph(letterBuff))
        {
            *pbuff = letterBuff;
            ++pbuff;
        }

        letterBuff = fgetc(fileInput);
    }

    *pbuff = '\0';
}

int	NotationCalculation(char operation, IntLIFO **number)
{
	int rightNumber;
	int leftNumber;

    leftNumber = PopInt(number);
    rightNumber = PopInt(number);
	switch(operation)
    {
        case('+'):
        {
            return rightNumber + leftNumber;
        }
        case('-'):
        {
            return rightNumber - leftNumber;
        }
        case('*'):
        {
            return rightNumber * leftNumber;
        }
        case('/'):
        {
            return rightNumber / leftNumber;
        }
        case('%'):
        {
            return rightNumber % leftNumber;
        }
        case('^'):
        {
            return pow(rightNumber, leftNumber);
        }
    }

	return 0;
}

int	operationPriority(char c)
{
    if (c == '^')
    {
        return 4;
    }
    if (c == '*' || c == '%' || c == '/')
    {
        return 3;
    }
    if (c == '+' || c == '-')
    {
        return 2;
    }
    if (c == '(')
    {
        return 1;
    }

    return 0;
}

void operation(char *operation, CharLIFO **operationLIFO, IntLIFO **numbersLIFO)
{
	if (*operationLIFO != NULL && operationPriority((*operationLIFO)->data) < operationPriority(*operation))
	{
        PushChar(operationLIFO, *operation);
	}
	else
	{
		while (*operationLIFO != 0 && operationPriority((*operationLIFO)->data) >= operationPriority(*operation))
		{
            PushInt(numbersLIFO, NotationCalculation(PopChar(operationLIFO), numbersLIFO));
		}
        PushChar(operationLIFO, *operation);
	}
}

int	checkingForCorrectBracket(char *expression, CharLIFO **operationLIFO, IntLIFO **numbersLIFO)
{
	if (*expression == '(')
    {
        PushChar(operationLIFO, *expression);
    }

	if (*expression == ')')
	{
		while (*operationLIFO != NULL && (*operationLIFO)->data != '(')
		{
            PushInt(numbersLIFO, NotationCalculation(PopChar(operationLIFO), numbersLIFO));
		}
		if (!(*operationLIFO))
        {
            return 0;
        }
        PopChar(operationLIFO);
	}
	return 1;
}

int	ExpressionCalculation(char *inputExpression, int *result)
{
    IntLIFO	*numberLIFO = NULL;
    CharLIFO *operationLIFO = NULL;
	char *operationArray = "*%/-+^",
	     *pInputExpression = inputExpression;

	while (*pInputExpression != '\0')
	{
		if (*pInputExpression == '-' && *(pInputExpression - 1) <= '0' && *(pInputExpression - 1) >= '9') /* *(pInputExpression - 1) <= '0' && *(pInputExpression - 1) >= '9' */
        {
            PushInt(&numberLIFO, atoi(pInputExpression));
        }
		if (isdigit(*pInputExpression))
        {
            PushInt(&numberLIFO, atoi(pInputExpression));
        }
		if (strchr(operationArray, *pInputExpression) != NULL)
        {
            operation(pInputExpression, &operationLIFO, &numberLIFO);
        }
		if (*pInputExpression == '(' || *pInputExpression == ')')
        {
            if (!(checkingForCorrectBracket(pInputExpression, &operationLIFO, &numberLIFO)))
            {
                return 0;
            }
        }
        pInputExpression++;
	}

	while (operationLIFO != NULL)
	{
		if (numberLIFO == NULL)
        {
            return 0;
        }

		if (intLIFOSize(numberLIFO) < 2)
        {
		    return 0;
        }

        PushInt(&numberLIFO, NotationCalculation(PopChar(&operationLIFO), &numberLIFO));
	}

	*result = PopInt(&numberLIFO);

	return numberLIFO == 0 && operationLIFO == 0;
}