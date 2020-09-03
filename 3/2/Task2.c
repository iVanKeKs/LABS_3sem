//
// Created by ivankeks on 27.11.2019.
//

#include "Tasks.h"

int testNumberForFirst(const int number, const int l)
{
    int currentNumber = number,
        countOfUnits = 0;

    while(currentNumber)
    {
        if(currentNumber & 1)
        {
            ++countOfUnits;
        }
        currentNumber = currentNumber >> 1;
    }

    if(countOfUnits == l)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int testNumberForSecond(const int number, const int l)
{
    int currentNumber = number,
        countOfUnits = 0;

    while(currentNumber)
    {
        if(currentNumber & 1)
        {
            ++countOfUnits;
        }
        else
        {
            countOfUnits = 0;
        }

        if((countOfUnits == l) && ((currentNumber & 10) == 0))
        {
            return 1;
        }
        currentNumber = currentNumber >> 1;
    }
    return 0;
}


void lab2()
{
    int k, l,
        *firstConditionNumbers,
        numberOfFirstNumbers = 0,
        *secondConditionNumbers,
        numberOfSecondNumbers = 0;
    scanf("%d %d", &k ,&l);

    int endNumber = pow(2, k) - 1;
    // Цифры подходящее к первому условию
    firstConditionNumbers = NULL;
    // Цифры подходящее ко второму условию
    secondConditionNumbers = NULL;

    for(int i = 1; i < endNumber; ++i)
    {

        // Если число подходит под первое условие
        // Если число подходит под первое условие
        if(testNumberForFirst(i, l) == 1)
        {
            ++numberOfFirstNumbers;
            firstConditionNumbers = (int *)realloc(firstConditionNumbers, sizeof(int)*numberOfFirstNumbers);
            firstConditionNumbers[numberOfFirstNumbers-1] = i;
        }

        // Если число подходит под второе условие
        if(testNumberForSecond(i, l) == 1)
        {
            ++numberOfSecondNumbers;
            secondConditionNumbers = (int *)realloc(secondConditionNumbers, sizeof(int)*numberOfSecondNumbers);
            secondConditionNumbers[numberOfSecondNumbers-1] = i;
        }
    }

    for(int i = 0; i < numberOfFirstNumbers; ++i)
    {
        printf("%d ", firstConditionNumbers[i]);
    }

    printf("\n");
    for(int i = 0; i < numberOfSecondNumbers; ++i)
    {
        printf("%d ", secondConditionNumbers[i]);
    }

    free(firstConditionNumbers);
    free(secondConditionNumbers);
}