//
// Created by iVan on 01.09.2020.
//

#include "TechnicalMethods.h"

int readFromFile(FILE *fileInput, char *buff)
{
    char buffChar;

    while (!feof(fileInput))
    {
        buffChar = fgetc(fileInput);

        if (isspace(buffChar) || buffChar == EOF)
        {
            continue;
        }

        if (buffChar == ';')
        {
            *buff++ = buffChar;
            *buff = '\0';
            return 1;
        }

        *buff++ = tolower(buffChar);
    }

    *buff = '\0';
    return 0;
}

void parseInputString(char *buff, char *command, char *firstNode, char *secondNode)
{
    *firstNode = '\0';
    *secondNode = '\0';
    *command = '\0';
    char *pbuff;

    int lengthOfBuff = strlen(buff) - 2;

    if(strstr(buff + lengthOfBuff, ");") != nullptr)
    {
        buff[lengthOfBuff] = '\0';
    }
    else
    {
        return;
    }

    pbuff = strchr(buff, '(');
    *pbuff++ = '\0';
    strcpy(command, buff);
    strcpy(firstNode, pbuff);

    pbuff = firstNode;

    pbuff = strchr(pbuff, ',');
    if(pbuff != nullptr)
    {
        *pbuff++ = '\0';
        strcpy(secondNode, pbuff);
    }
}
