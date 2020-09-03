//
// Created by ivankeks on 29.11.2019.
//

#include "Students.h"


void killMassOfStudents(Students **mass, int numberOfStudents)
{
    if(mass == NULL)
    {
        return;
    }

    for(int i = 0; i < numberOfStudents; ++i)
    {
        free(mass[i]);
    }

    free(mass);
}


int readNextOfStudents(FILE *fin, Students *NewNode)
{
    char bufChar[BUFSIZ],
            bufCh,
            *pbuf = bufChar;

    if(feof(fin))
    {
        return -1;
    }

    bufCh = fgetc(fin);
    while(!isspace(bufCh))
    {
        *pbuf = bufCh;
        ++pbuf;
        bufCh = fgetc(fin);
    }
    *pbuf = '\0';
    pbuf = bufChar;
    NewNode->id = atoi(bufChar);

    bufCh = fgetc(fin);
    while(!isspace(bufCh))
    {
        *pbuf = bufCh;
        ++pbuf;
        bufCh = fgetc(fin);
    }
    *pbuf = '\0';
    pbuf = bufChar;
    strcpy(NewNode->name, bufChar);

    bufCh = fgetc(fin);
    while(!isspace(bufCh))
    {
        *pbuf = bufCh;
        ++pbuf;
        bufCh = fgetc(fin);
    }
    *pbuf = '\0';
    pbuf = bufChar;
    strcpy(NewNode->surname, bufChar);

    bufCh = fgetc(fin);
    while(bufCh != '\n' && bufCh != EOF)
    {
        *pbuf = bufCh;
        ++pbuf;
        bufCh = fgetc(fin);
    }
    *pbuf = '\0';
    strcpy(NewNode->group, bufChar);

    return 0;
}


Students *searchById(char *id, Students **massOfStudents, int numberOfStudents)
{
    int bufId = atoi(id);
    Students *foundedStudent;

    for(int i = 0; i < numberOfStudents; ++i)
    {
        if(massOfStudents[i]->id == bufId)
        {
            printf("%d %s %s %s\n", massOfStudents[i]->id,
                                         massOfStudents[i]->name,
                                         massOfStudents[i]->surname,
                                         massOfStudents[i]->group);

            foundedStudent = massOfStudents[i];
            return foundedStudent;
        }
    }

    printf("Студент не найден\n");
    return NULL;
}


Students **searchByName(char *name, Students **massOfStudents, int numberOfStudents)
{
    int founded = 0;
    Students **foundedStudents = NULL;
    for(int i = 0; i < numberOfStudents; ++i)
    {
        if(!strcmp(massOfStudents[i]->name, name))
        {
            ++founded;
            printf("%d %s %s %s\n", massOfStudents[i]->id,
                                         massOfStudents[i]->name,
                                         massOfStudents[i]->surname,
                                         massOfStudents[i]->group);
            foundedStudents = (Students **)realloc(foundedStudents, founded);
            foundedStudents[founded-1] = massOfStudents[i];
        }
    }

    if(founded == 0)
    {
        printf("Студент не найден\n");
        return NULL;
    }
    else
    {
        printf("Найдено %d записей\n", founded);
        return foundedStudents;
    }
}


Students **searchBySurname(char *surname, Students **massOfStudents, int numberOfStudents)
{
    int founded = 0;
    Students **foundedStudents = NULL;

    for(int i = 0; i < numberOfStudents; ++i)
    {
        if(!strcmp(massOfStudents[i]->surname, surname))
        {
            ++founded;
            printf("%d %s %s %s\n", massOfStudents[i]->id,
                                         massOfStudents[i]->name,
                                         massOfStudents[i]->surname,
                                         massOfStudents[i]->group);

            foundedStudents = (Students **)realloc(foundedStudents, founded);
            foundedStudents[founded-1] = massOfStudents[i];
        }
    }

    if(founded == 0)
    {
        printf("Студент не найден\n");
        return NULL;
    }
    else
    {
        printf("Найдено %d записей\n", founded);
        return foundedStudents;
    }
}


Students **searchByGroup(char *group, Students **massOfStudents, int numberOfStudents)
{
    int founded = 0;
    Students **foundedStudents = NULL;

    for(int i = 0; i < numberOfStudents; ++i)
    {
        if(!strcmp(massOfStudents[i]->group, group))
        {
            ++founded;
            printf("%d %s %s %s\n", massOfStudents[i]->id,
                                         massOfStudents[i]->name,
                                         massOfStudents[i]->surname,
                                         massOfStudents[i]->group);

            foundedStudents = (Students **)realloc(foundedStudents, sizeof(Students*)*founded);
            foundedStudents[founded-1] = massOfStudents[i];
        }
    }

    if(founded == 0)
    {
        printf("Студент не найден\n");
        return NULL;
    }
    else
    {
        printf("Найдено %d записей\n", founded);
        return foundedStudents;
    }
}