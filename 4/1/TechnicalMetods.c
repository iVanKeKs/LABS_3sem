//
// Created by iVan on 11.08.2020.
//

#include "TechnicalMetods.h"

char *errors[] = {"Не обнаруженны параметры командной строки",
                  "Нет такого файла",
                  "Нет такого массива",
                  "Массив слишком короткий",
                  "Не верные значения индекса",
                  "Неверная комманда"};

void error(int errorNumber)
{
    printf("Error: %s", errors[errorNumber-1]);
    exit(errorNumber);
}

int sortFromLargestToSmallest(const int *leftElement, const int *rightElement)
{
    return *rightElement - *leftElement;
}

int sortFromSmallestToLargest(const int *leftElement, const int *rightElement)
{
    return *leftElement - *rightElement;
}

void readFromFile(FILE *fileInput, char *buff)
{
    char *pbuff = buff,
          buffChar;

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