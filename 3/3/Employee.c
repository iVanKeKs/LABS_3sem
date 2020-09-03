//
// Created by ivankeks on 27.11.2019.
//

#include "Employee.h"

void killMass(Employee **mass, int numberOfEmployees)
{
    if(mass == NULL)
    {
        return;
    }

    for(int i = 0; i < numberOfEmployees; ++i)
    {
        free(mass[i]->name);
        free(mass[i]->surname);
        free(mass[i]);
    }

    free(mass);
}


int readNext(FILE *fin, Employee *NewNode)
{
    char bufChar[BUFSIZ];

    if(feof(fin))
    {
        return -1;
    }

    fscanf(fin, "%d", &NewNode->id);

    fscanf(fin, "%s", bufChar);
    NewNode->name = (char *)malloc(strlen(bufChar));
    strcpy(NewNode->name, bufChar);

    fscanf(fin, "%s", bufChar);
    NewNode->surname = (char *)malloc(strlen(bufChar));
    strcpy(NewNode->surname, bufChar);

    fscanf(fin, "%d", &NewNode->pay);

    return 0;
}