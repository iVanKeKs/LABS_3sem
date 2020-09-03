//
// Created by ivankeks on 27.11.2019.
//

#include "Tasks.h"
#include "Employee.h"

int func(Employee **firstNode, Employee **secondNode)
{
    return (*firstNode)->pay - (*secondNode)->pay;
}

void lab3(char *fileIn, char *fileOut)
{
    FILE *fin, *fout;
    if(!(fin = fopen(fileIn, "r")))
    {
        perror("fileInput");
        exit(-1);
    }

    if(!(fout = fopen(fileOut, "w")))
    {
        perror("fileOutput");
        exit(-1);
    }

    int numberOfEmployees = 0;
    Employee **massOFEmployee = NULL,
             *pNewNode;
    while(1)
    {
        pNewNode = (Employee *)malloc(sizeof(Employee));
        if(readNext(fin, pNewNode) == -1)
        {
            free(pNewNode);
            break;
        }
        ++numberOfEmployees;
        massOFEmployee = (Employee **)realloc(massOFEmployee, numberOfEmployees * sizeof(Employee*));
        massOFEmployee[numberOfEmployees-1] = pNewNode;

    }

    qsort(massOFEmployee, numberOfEmployees, sizeof(Employee**), func);

    Employee *curr;
    for(int i = 0; i < numberOfEmployees; ++i)
    {
        curr = massOFEmployee[i];
        fprintf(fout, "%d ", curr->id);
        fprintf(fout, "%s ", curr->name);
        fprintf(fout, "%s ", curr->surname);
        fprintf(fout, "%d\n", curr->pay);
    }

    killMass(massOFEmployee, numberOfEmployees);
    fclose(fin);
    fclose(fout);
}