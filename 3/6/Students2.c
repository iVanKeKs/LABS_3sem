//
// Created by ivankeks on 30.11.2019.
//

#include "Students2.h"

int readNextStudents2(FILE *fin, Student2 *stud)
{
    char buff[BUFSIZ];

    if(feof(fin))
    {
        return -1;
    }

    // Фамилия
    fscanf(fin, "%s", buff);
    stud->surname = (char *)malloc(strlen(buff));
    strcpy(stud->surname, buff);

    // Имя
    fscanf(fin, "%s", buff);
    stud->name = (char *)malloc(strlen(buff));
    strcpy(stud->name, buff);

    // Отчество
    fscanf(fin, "%s", buff);
    stud->patronymic = (char *)malloc(strlen(buff));
    strcpy(stud->patronymic, buff);

    // Группа
    fscanf(fin, "%s", buff);
    stud->group = (char *)malloc(strlen(buff));
    strcpy(stud->group, buff);

    fscanf(fin, "%d", &stud->firstExam);
    fscanf(fin, "%d", &stud->secondExam);
    fscanf(fin, "%d", &stud->thirdExam);
    fscanf(fin, "%d", &stud->fourthExam);
    fscanf(fin, "%d", &stud->fifthExam);

    return 0;
}


void printMiddle(Student2 **massOfStudents, double *massOfMiddle, double middle, int numberOfStudents)
{
    for(int i = 0; i < numberOfStudents; ++i)
    {
        if((middle - massOfMiddle[i]) < 0.0000000002244)
        {
            printf("%s %s %s %s %.2f\n", massOfStudents[i]->surname,
                                              massOfStudents[i]->name,
                                              massOfStudents[i]->patronymic,
                                              massOfStudents[i]->group,
                                              massOfMiddle[i]);
        }
    }
}


void killMassOfStud2(Student2 **massOfStud, int numberOfStudents)
{
    if(massOfStud == NULL)
    {
        return;
    }

    for(int i = 0; i < numberOfStudents; ++i)
    {
        free(massOfStud[i]);
    }

    free(massOfStud);
}