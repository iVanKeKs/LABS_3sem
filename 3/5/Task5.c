//
// Created by ivankeks on 29.11.2019.
//

#include <string.h>

#include "Tasks.h"
#include "Students.h"

void lab5(char *fileIn)
{
    FILE *fin;
    if(!(fin = fopen(fileIn, "r")))
    {
        perror("input file");
        exit(-1);
    }

    Students **massOfStudents = NULL;

    int numberOfStudents = 0;
    Students *pNewNode;
    while(1)
    {
        pNewNode = (Students *)malloc(sizeof(Students));
        if(readNextOfStudents(fin, pNewNode) == -1)
        {
            free(pNewNode);
            break;
        }
        ++numberOfStudents;
        massOfStudents = (Students **)realloc(massOfStudents, numberOfStudents * sizeof(Students*));
        massOfStudents[numberOfStudents - 1] = pNewNode;

    }

    char buff[BUFSIZ],
         ch;
      //   *commands[] = {"ID", "Имя", "Фамилия", "Группа"};

      /*
    void *funcs = {searchById(buff, massOfStudents, numberOfStudents),
                   searchByName(buff, massOfStudents, numberOfStudents),
                   searchBySurname(buff, massOfStudents, numberOfStudents),
                   searchByGroup(buff, massOfStudents, numberOfStudents)};*/

    while(1)
    {
        scanf("%s", buff);
        if(!strcmp("Stop", buff))
        {
            killMassOfStudents(massOfStudents, numberOfStudents);
            return;
        }

        if(!strcmp("ID", buff))
        {
            scanf("%s", buff);
            Students *foundedStudent = searchById(buff, massOfStudents, numberOfStudents);
            free(foundedStudent);
            continue;
        }

        if(!strcmp("Имя", buff))
        {
            scanf("%s", buff);
            Students **foundedStudent = searchByName(buff, massOfStudents, numberOfStudents);
            free(foundedStudent);
            continue;
        }

        if(!strcmp("Фамилия", buff))
        {
            scanf("%s", buff);
            Students **foundedStudent = searchBySurname(buff, massOfStudents, numberOfStudents);
            free(foundedStudent);
            continue;
        }

        if(!strcmp("Группа", buff))
        {
            scanf("%s", buff);
            Students **foundedStudent = searchByGroup(buff, massOfStudents, numberOfStudents);
            free(foundedStudent);
            continue;
        }
        else
        {
            printf("Введена не верная команда\n");
        }
    }
}