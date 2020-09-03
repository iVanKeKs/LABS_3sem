//
// Created by iVan on 02.09.2020.
//

#include "TechnicalMethods.h"

void ReadFromFile(FILE *fileInput, char *buff)
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
            break;
        }
        else
        {
            *buff++ = tolower(buffChar);
        }

    }

    *buff = '\0';
}


void ParseInputString(char *buff, char *command, char *firstArgument, char *secondArgument)
{
    int lengthOfBuff = strlen(buff) - 2;
    if(strstr(buff + lengthOfBuff, ">;") != nullptr && *(buff) == '<')
    {
        buff[lengthOfBuff] = '\0';
        ++buff;
    }
    else
    {
        return;
    }

    *firstArgument = '\0';
    *secondArgument = '\0';
    *command = '\0';
    char *pbuff = buff;

    while(*pbuff != '\0')
    {
        if (*pbuff == '>')
        {
            *pbuff = '\0';
            strcpy(firstArgument, buff);
            ++pbuff;
            strcpy(command, pbuff);
            break;
        }

        ++pbuff;
    }

    pbuff = command;

    while(*pbuff != '\0')
    {
        if (*pbuff == '<')
        {
            *pbuff = '\0';
            ++pbuff;
            strcpy(secondArgument, pbuff);
            break;
        }

        ++pbuff;
    }
}