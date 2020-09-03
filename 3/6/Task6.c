//
// Created by ivankeks on 30.11.2019.
//

#include "Students2.h"

void lab6(char *fileInput)
{
    FILE *fin, *fout;
    if(!(fin = fopen(fileInput, "r")))
    {
        perror("file input");
        exit(-1);
    }

    if(!(fout = fopen("out6.txt", "w")))
    {
        perror("file output");
        exit(-1);
    }

    Student2 **massOfStudents = NULL;
    Student2 *pNewNode;
    int numberOfStudents = 0;

    double middleOfAll = 0,
           *massOfMiddle = NULL,
            currentMiddle = 0;

    while(1)
    {
        pNewNode = (Student2 *)malloc(sizeof(Student2));
        if(readNextStudents2(fin, pNewNode) == -1)
        {
            free(pNewNode);
            break;
        }

        ++numberOfStudents;
        massOfStudents = (Student2 **)realloc(massOfStudents, numberOfStudents * sizeof(Student2*));
        massOfStudents[numberOfStudents - 1] = pNewNode;

        currentMiddle = (pNewNode->firstExam +
                         pNewNode->secondExam +
                         pNewNode->thirdExam +
                         pNewNode->fourthExam +
                         pNewNode->fifthExam) / 5.;

        fprintf(fout, "%s %s %s %s %.2f\n", pNewNode->surname,
                                               pNewNode->name,
                                               pNewNode->patronymic,
                                               pNewNode->group,
                                               currentMiddle);

        massOfMiddle = (double *)realloc(massOfMiddle, sizeof(double) * numberOfStudents);
        massOfMiddle[numberOfStudents-1] = currentMiddle;
    }

    for(int i = 0; i < numberOfStudents; ++i)
    {
        middleOfAll += massOfMiddle[i];
    }

    middleOfAll /= numberOfStudents;

    printMiddle(massOfStudents, massOfMiddle, middleOfAll, numberOfStudents);

    killMassOfStud2(massOfStudents, numberOfStudents);
    free(massOfMiddle);
    fclose(fin);
    fclose(fout);
}