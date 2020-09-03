//
// Created by ivankeks on 02.12.2019.
//

#include "String.h"

String *creatString(char *dataForNewString)
{
    String *newString = (String *)malloc(sizeof(String));

    if(dataForNewString == NULL)
    {
        newString->data = NULL;
        newString->sizeOfString = 0;
    }
    else
    {
        unsigned int sizeOfString = strlen(dataForNewString);
        newString->data = (char *)malloc(sizeOfString+1);
        newString->sizeOfString = sizeOfString;
        strcpy(newString->data, dataForNewString);
    }

    return newString;
}


void killString(String *str)
{
    if(str == NULL)
    {
        return;
    }

    free(str->data);
    free(str);
}


unsigned int cmpStrings(String *str1, String *str2)
{
    if(str1 == NULL)
    {
        if(str2 == NULL)
        {
            return 0;
        }
        return 0 - str2->sizeOfString;
    }

    if(str2 == NULL)
    {
        return str1->sizeOfString;
    }

    for(unsigned int i = 0; i < str1->sizeOfString; ++i)
    {
        if(str1->data[i] != str2->data[i])
        {
            return str1->data[i] - str2->data[i];
        }

        if(str1->data[i] == '\0')
        {
            return 0;
        }
    }

    return 0;
}


int cntStrings(String *str1, String *str2)
{
    if(str1 == NULL || str2 == NULL)
    {
        return -1;
    }

    if(str1->data == NULL)
    {
        return 0;
    }

    unsigned int buffSize = str2->sizeOfString;
    str2->data = (char *)realloc(str2->data, str1->sizeOfString + str2->sizeOfString + 1);
    str2->sizeOfString += str1->sizeOfString;

    for(unsigned int i = 0; i < str2->sizeOfString; ++i)
    {
        str2->data[buffSize + i] = str1->data[i];
    }

    return 0;
}


String *copyString(String *str)
{
    String *newStr;
    if(str->sizeOfString == 0)
    {
        newStr = creatString(NULL);
    }
    else
    {
        newStr = (String *)malloc(sizeof(String));
        newStr->data = (char *)malloc(str->sizeOfString + 1);
        newStr->sizeOfString = str->sizeOfString;
        strcpy(newStr->data, str->data);
    }

    return newStr;
}