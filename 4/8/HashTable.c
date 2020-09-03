//
// Created by iVan on 27.08.2020.
//

#include "HashTable.h"

list *newList(char *nameOfDefine, char *valueOfDefine)
{
    list *newDefine;

    newDefine = (list*)malloc(sizeof(list));

    newDefine->next = NULL;

    newDefine->nameOfDefine = (char*)malloc(sizeof(char) * (strlen(nameOfDefine) + 1));
    strcpy(newDefine->nameOfDefine, nameOfDefine);

    newDefine->value = (char*)malloc(sizeof(char) * (strlen(valueOfDefine) + 1));
    strcpy(newDefine->value, valueOfDefine);

    return newDefine;
}

char *searchDefine(list *currentNode, char *buff)
{
    while (currentNode && strcmp(currentNode->nameOfDefine, buff) == 0)
    {
        currentNode = currentNode->next;
    }

    if (currentNode != NULL)
    {
        return currentNode->value;
    }

    return buff;
}

void pushNewDefine(list **arrayOfDefine, char *value, char *nameOfDefine)
{
    list *newDefine;

    newDefine = newList(nameOfDefine, value);

    newDefine->next = *arrayOfDefine;

    *arrayOfDefine = newDefine;
}

int	getHashCode(char *nameOfDefine)
{
    int result = 0;

    while (*nameOfDefine != '\0')
    {
        result = result*62 + isdigit(tolower(*nameOfDefine)) ? *nameOfDefine - '0' : 10 + *nameOfDefine - 'a';
        result %= HASHSIZE;
        nameOfDefine++;
    }
    return result;
}

void parseInputString(char *buff, list **hashTable, FILE *fileInput, char lastReadSymbol, FILE *fileOutput)
{
    char buffChar;

    char nameOfDefine[BUFSIZ],
         value[BUFSIZ],
         *pDefine = nameOfDefine,
         *pValue = value;

    int hash;

    if (strcmp(buff, "#define") == 0)
    {
        fprintf(fileOutput, "%s", buff);

        while ((buffChar = fgetc(fileInput)) != ' ')
        {
            fprintf(fileOutput, "%c", buffChar);

            *pDefine++ = buffChar;
        }
        fprintf(fileOutput, " ");
        *pDefine = '\0';

        while ((buffChar = fgetc(fileInput)) != '\n' && buffChar != EOF)
        {
            fprintf(fileOutput, "%c", buffChar);

            *pValue++ = buffChar;
        }
        *pValue = '\0';

        hash = getHashCode(nameOfDefine);
        pushNewDefine(&hashTable[hash], value, nameOfDefine);

        return ;
    }

    hash = getHashCode(buff);
    if (lastReadSymbol != EOF)
    {
        fprintf(fileOutput, "%s%c", searchDefine(hashTable[hash], buff), lastReadSymbol);
    }
    else
    {
        fprintf(fileOutput, "%s", searchDefine(hashTable[hash], buff));
    }
}

void readFromFileAndParse(list **hashTable, FILE *fileInput)
{
    char buffChar,
         buff[BUFSIZ],
         *pbuff = buff;

    FILE *fileOutput = fopen("result.txt", "w");

    while (!feof(fileInput))
    {
        buffChar = fgetc(fileInput);

        if (isspace(buffChar) || buffChar == EOF)
        {
            *pbuff = '\0';
            parseInputString(buff, hashTable, fileInput, buffChar, fileOutput);

            if (buffChar == EOF)
            {
                break ;
            }

            pbuff = buff;

            continue;
        }

        *pbuff++ = buffChar;
    }
}

void freeList(list *currentNode)
{
    list *buff;

    while (currentNode != NULL)
    {
        buff = currentNode;
        currentNode = currentNode->next;
        free(buff);
    }
}

void freeArrayOfList(list **array)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        freeList(array[i]);
    }
}