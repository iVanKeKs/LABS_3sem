//
// Created by iVan on 20.08.2020.
//

#ifndef INC_4_SOMETOWN_H
#define INC_4_SOMETOWN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LENGTH_WITHOUT_FILES 1
#define DATES_ARE_EQUAL 0

typedef struct __recordAboutCitizen Citizen;
typedef struct __list List;

struct __recordAboutCitizen
{
    char name[30];
    char surname[30];
    char patronymic[30];
    char dataOfBirth[12];
    char gender;
    int salary;
};

struct __list
{
    Citizen	record;
    List *next;
};

void readRecordsFromFile(FILE *fileInput, List **listRecord);

List *createList(Citizen newHeadOfList);
void pushRecord(List **headOfList, Citizen newRecord);
void removeRecord(List **listRecord, char *name);
void freeList(List **headOfList);

void copyRecord(Citizen *copyOfRecord, Citizen *sourceRecord);
int	compareDates(char *firstDate, char *secondDate);
void printList(List **headOfList);
List *searchRecord(List **listRecord, char *name);
void saveListInFile(List **listRecord);

#define ERROR_NO_FILES_IN_ARGS 1
#define ERROR_FILE_NOT_EXIST ERROR_NO_FILES_IN_ARGS + 1
void error(int errorNumber);

#endif //INC_4_SOMETOWN_H
