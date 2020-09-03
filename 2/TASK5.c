//
// Created by iVan on 29.09.2019.
//

#include "Tasks.h"

void WritingMassFromBuff(char* str, char *buff)
{
    static int i = 0;
    int j = -1;

    while(buff[++j] != '\0')
    {
        str[i++] = buff[j];
    }
}

//Сортировка: цифры, буквы, прочие
void SortingStr(char *str)
{
    char buff1[BUFSIZ], buff2[BUFSIZ], buff3[BUFSIZ];

    int i = -1;
    int index1 = 0, index2 = 0, index3 = 0;
    while(str[++i] != '\0')
    {
        if(isdigit(str[i]))
        {
            buff1[index1] = str[i];
            ++index1;
            continue;
        }

        if(isalpha(str[i]))
        {
            buff2[index2] = str[i];
            ++index2;
        }
        else
        {
            buff3[index3] = str[i];
            ++index3;
        }
    }

    WritingMassFromBuff(str, buff1);
    WritingMassFromBuff(str, buff2);
    WritingMassFromBuff(str, buff3);
}