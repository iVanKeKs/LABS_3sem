//
// Created by iVan on 07.10.2019.
//

#include "Tasks.h"

//Подсчет колличества букв в строк

int countLetter(const char *str)
{
    int countOfLitters = 0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        if(isalpha(str[i]))
        {
            countOfLitters++;
        }
    }

    return countOfLitters;
}


//Начало метода
void lab10(FILE *fileInput)
{
    FILE *fout;
    if(!(fout = fopen("out.txt", "w")))
    {
        printf("Не удалось открыть файл на запись");
        exit(-1);
    }

    char buff[BUFSIZ],
         litterBuff;
    int i = -1;

    while(1)
    {
        litterBuff = fgetc(fileInput);

        //Выход в случае если EOF
        if(litterBuff == EOF)
        {
            buff[++i] = '\0';
            fprintf(fout, "%d", countLetter(buff));
            fclose(fout);
            return;
        }

        //Нова строка
        if(litterBuff == '\n')
        {
            buff[++i] = '\0';
            i = -1;
            fprintf(fout, "%d\n", countLetter(buff));
        }
        //
        else
        {
            buff[++i] = litterBuff;
        }
    }
}