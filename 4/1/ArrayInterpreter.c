//
// Created by iVan on 11.08.2020.
//

#include "ArrayInterpreter.h"

Array arrayOfVariables[26];

void (*arrayOfFunctionPointers[NUMBER_OF_OPERATION])(char*) =
        {loadArrayFromFile, saveArrayToFile, randomizeArray, concatenationArray,
         freeArray, removeElementsFromArray, copyArray, sortArray,
         permuteArray, informationAboutArray, printArray};

char *arrayOfFunctionNames[NUMBER_OF_OPERATION] = {"load", "save", "rand", "concat",
                                                   "free", "remove", "copy", "sort",
                                                   "permute", "stat", "print"};

void searchAndExeOperation(char *str)
{
    static int numberOfCall = 1;
    for (int i = 0; i < NUMBER_OF_OPERATION; i++)
    {
        if (strstr(str, arrayOfFunctionNames[i]))
        {
            printf("%d: %s\n", numberOfCall++, str);
            arrayOfFunctionPointers[i](str);
            break ;
        }
    }

}

void loadArrayFromFile(char *inputString)
{
    FILE *fileInput;
    char buff[BUFSIZ],
         *pbuff = buff,
         buffChar;

    int numberOfArray = *(inputString + 5) - 'a',
        sizeOfArrayInFile = 0;

    if (!(fileInput = fopen(inputString + 8, "r")))
    {
        error(ERROR_FILE_NOT_EXIST);
    }

    Array *newArray = arrayOfVariables + numberOfArray;

    while (!feof(fileInput))
    {
        buffChar = getc(fileInput);
        if(!isspace(buffChar) && buffChar != EOF)
        {
            *pbuff++ = buffChar;
        }
        else
        {
            *pbuff = '\0';
            pbuff = buff;

            ++sizeOfArrayInFile;
            if (newArray->size == 0)
            {
                newArray->size = 1;
                newArray->data = (int *)malloc(sizeof(int));
                newArray->data[0] = atoi(buff);
            }
            else
            {
                if(sizeOfArrayInFile > newArray->size)
                {
                    newArray->size += 1;
                    newArray->data = (int *)realloc(newArray->data, sizeof(int) * newArray->size);
                    newArray->data[sizeOfArrayInFile - 1] = atoi(buff);
                }
                else
                {
                    newArray->data[sizeOfArrayInFile - 1] = atoi(buff);
                }
            }
        }
    }

    fclose(fileInput);
}

void saveArrayToFile(char *inputString)
{
    FILE *fileOutput;
    int numberOfArray = *(inputString + 5) - 'a';;

    if (!(fileOutput = fopen(inputString + 8, "w")))
    {
        error(ERROR_FILE_NOT_EXIST);
    }

    Array *currentArray = arrayOfVariables + numberOfArray;
    if (currentArray->size == 0)
    {
        error(ERROR_ARRAY_NOT_EXIST);
    }

    for (int i = 0; i < currentArray->size; ++i)
    {
        fprintf(fileOutput, "%d", currentArray->data[i]);
        if(i != currentArray->size - 1)
        {
            fprintf(fileOutput, " ");
        }
    }

    fclose(fileOutput);
}

void concatenationArray(char *inputString)
{
    int numberOfFirstArray = *(inputString + 7) - 'a',
        numberOfSecondArray = *(inputString + 10) - 'a';
    Array *firstArray = arrayOfVariables + numberOfFirstArray,
          *secondArray = arrayOfVariables + numberOfSecondArray;

    if (firstArray->size == 0)
    {
        error(ERROR_ARRAY_NOT_EXIST);
    }
    if (secondArray->size == 0)
    {
        error(ERROR_ARRAY_NOT_EXIST);
    }

    firstArray->size += secondArray->size;
    firstArray->data = (int*)realloc(firstArray->data, sizeof(int) * firstArray->size);

    for (int j = 0, i = firstArray->size - secondArray->size; i < firstArray->size; ++i, ++j)
    {
        firstArray->data[i] = secondArray->data[j];
    }
}

void randomizeArray(char *inputString)
{
    char *pStr = inputString + 5;

    int numberOfNewArray,
        sizeOfNewArray = 0,
        leftBound = 0,
        rightBound = 0;

    srand(time(NULL));

    numberOfNewArray = *pStr - 'a';
    pStr += 2;
    sizeOfNewArray = atoi(pStr);

    pStr = strchr(pStr, ',');
    leftBound = atoi(++pStr);

    pStr = strchr(pStr, ',');
    rightBound = atoi(++pStr);

    Array *newArray = arrayOfVariables + numberOfNewArray;
    newArray->size = sizeOfNewArray;
    newArray->data = (int*)malloc(sizeof(int) * sizeOfNewArray);

    for (int i = 0; i < sizeOfNewArray; ++i)
    {
        newArray->data[i] = rand() % ((abs(leftBound)) + (abs(rightBound))) - (abs(leftBound));
    }
}

void freeArray(char *inputString)
{
    int numberOfCurrentArray = *(inputString + 5) - 'a';

    arrayOfVariables[numberOfCurrentArray].size = 0;
    free(arrayOfVariables[numberOfCurrentArray].data);
}

void removeElementsFromArray(char *inputString)
{
    char *pStr = inputString + 7;
    int numberOfCurrentArray = *pStr - 'a',
        firstElementToRemove = 0,
        numberOfElementsToRemove = 0;


    pStr += 3;
    firstElementToRemove = atoi(pStr);

    inputString = strchr(pStr, ',');
    numberOfElementsToRemove = atoi(++inputString);

    Array *currentArray = arrayOfVariables + numberOfCurrentArray;
    if (firstElementToRemove + numberOfElementsToRemove >= currentArray->size)
    {
        error(ERROR_ARRAY_IS_SHORT);
    }

    for (int i = firstElementToRemove; i < numberOfElementsToRemove + firstElementToRemove; i++)
    {
        currentArray->data[i] = currentArray->data[i + numberOfElementsToRemove];
    }

    currentArray->size -= numberOfElementsToRemove;
    currentArray->data = (int*)realloc(currentArray->data, sizeof(int) * currentArray->size);
}

void copyArray(char *inputString)
{
    char *pStr = inputString + 5;
    int numberOfSourceArray = *(pStr) - 'a',
        numberOfNewArray,

        indexOfFirstElementToCopy,
        indexOfLastElementToCopy;

    pStr = strchr(pStr, ',');
    indexOfFirstElementToCopy = atoi(++pStr);

    pStr = strchr(pStr, ',');
    indexOfLastElementToCopy = atoi(++pStr);

    numberOfNewArray = pStr[strlen(pStr) - 1] - 'a';

    Array *sourceArray = arrayOfVariables + numberOfSourceArray,
          *newArray = arrayOfVariables + numberOfNewArray;

    if(indexOfFirstElementToCopy < 0 || indexOfLastElementToCopy < 0 ||
       indexOfFirstElementToCopy > indexOfLastElementToCopy)
    {
        error(ERROR_INVALID_INDEX);
    }

    if (indexOfLastElementToCopy >= sourceArray->size || indexOfFirstElementToCopy >= sourceArray->size)
    {
        error(ERROR_ARRAY_IS_SHORT);
    }

    newArray->size += (indexOfLastElementToCopy - indexOfFirstElementToCopy + 1);
    newArray->data = (int*)realloc(newArray->data, sizeof(int) * newArray->size);

    for (int j = indexOfFirstElementToCopy, i = newArray->size - (indexOfLastElementToCopy - indexOfFirstElementToCopy + 1); i < newArray->size; ++j, ++i)
    {
        newArray->data[i] = sourceArray->data[j];
    }
}

void sortArray(char *inputString)
{
    int numberOfCurrentArray = *(inputString + 5) - 'a';

    if (arrayOfVariables[numberOfCurrentArray].size == 0)
    {
        error(ERROR_ARRAY_NOT_EXIST);
    }

    Array *currentArray = arrayOfVariables + numberOfCurrentArray;

    switch(*(inputString + 6))
    {
        case('+'):
        {
            qsort(currentArray->data, currentArray->size, sizeof(int),
                  (int (*)(const void *, const void *)) sortFromSmallestToLargest);
            break;
        }

        case('-'):
        {
            qsort(currentArray->data, currentArray->size, sizeof(int),
                  (int (*)(const void *, const void *)) sortFromLargestToSmallest);
            break;
        }

        default:
        {
            error(ERROR_INVALID_COMMAND);
        }
    }
}

void permuteArray(char *inputString)
{
    int numberOfCurrentArray = *(inputString + 8) - 'a';
    int buff;
    int newRandomPosition;

    srand(time(NULL));

    Array *currentArray = arrayOfVariables + numberOfCurrentArray;
    for (int i = 0; i < currentArray->size; i++)
    {
        newRandomPosition = rand() % currentArray->size;
        buff = currentArray->data[newRandomPosition];

        currentArray->data[newRandomPosition] = currentArray->data[i];
        currentArray->data[i] = buff;
    }

}

void informationAboutArray(char *inputString)
{
    int numberOfCurrentArray = *(inputString + 5) - 'a';
    Array *currentArray = arrayOfVariables + numberOfCurrentArray;

    int minElementOfArray = currentArray->data[0],
        maxElementOfArray = currentArray->data[0];

    int indexMinElementOfArray = 0,
        indexMaxElementOfArray = 0;

    int sumOfElements = 0;

    int frequentElement = currentArray->data[0],
        maxFrequent = 1;

    int countEqualElements;

    if (currentArray->size == 0)
    {
        error(ERROR_ARRAY_NOT_EXIST);
    }

    for (int i = 0; i < currentArray->size; i++)
    {
        countEqualElements = 0;
        for (int j = 0; j < currentArray->size; j++)
        {
            if (currentArray->data[j] == currentArray->data[i])
            {
                countEqualElements++;
            }
        }
        if (countEqualElements > maxFrequent)
        {
            maxFrequent = countEqualElements;
            frequentElement = currentArray->data[i];
        }

        if (minElementOfArray > currentArray->data[i])
        {
            minElementOfArray = currentArray->data[i];
            indexMinElementOfArray = i;
        }
        if (maxElementOfArray < currentArray->data[i])
        {
            maxElementOfArray = currentArray->data[i];
            indexMaxElementOfArray = i;
        }

        sumOfElements += currentArray->data[i];
    }
    sumOfElements = sumOfElements / currentArray->size;

    printf("Массив %c:\nРазмер: %d\nМаксимальный элемент: %d\nИндекс максимального элемента: %d\nМинимальный элемент: %d\nИндекс минимального элемента: %d\nЧасто встречающийся элемент: %d\nСреднее значение элементов: %d\nМаксимальное отклонение: %d\n",
            *(inputString + 5), currentArray->size, maxElementOfArray, indexMaxElementOfArray, minElementOfArray, indexMinElementOfArray, frequentElement, sumOfElements, MAX(abs(sumOfElements - maxElementOfArray), abs(sumOfElements - minElementOfArray)));
}

void printArray(char *inputString)
{
    if (strcmp(inputString + 6, "all") == 0)
    {
        for (int i = 0; i < 26; i++)
        {
            if (arrayOfVariables[i].size)
            {
                printf("%c: ", i + 'A');
                for (int j = 0; j < arrayOfVariables[i].size; j++)
                {
                    printf("%d ", arrayOfVariables[i].data[j]);
                }
                printf("\n");
            }
        }
    }
    else
    {
        char *pStr = inputString + 6;
        int numberOfCurrentArray = *pStr - 'a',
            leftBound,
            rightBound;

        Array *currentArray = arrayOfVariables + numberOfCurrentArray;

        if(strcmp(pStr + 3, "all") == 0)
        {
            leftBound = 0;
            rightBound = currentArray->size;
        }
        else
        {
            pStr += 3;
            leftBound = atoi(pStr);

            pStr = strchr(pStr, ',');
            rightBound = atoi(++pStr) + 1;
        }

        printf("%c: ", toupper(*(inputString + 6)));
        for (int i = leftBound; i < rightBound; ++i)
        {
            printf("%d ", currentArray->data[i]);
        }

        printf("\n");
    }
}