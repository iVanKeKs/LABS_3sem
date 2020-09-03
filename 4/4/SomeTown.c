//
// Created by iVan on 20.08.2020.
//

#include "SomeTown.h"

List *createList(Citizen newHeadOfList)
{
    List *newList = (List*)malloc(sizeof(List));

    newList->next = NULL;
    copyRecord(&newList->record, &newHeadOfList);

    return newList;
}


void readFromFile(FILE *fileInput, char *buff)
{
    char buffChar,
         *pbuff = buff;

    while((buffChar = getc(fileInput)) != '\r' && buffChar != EOF)
    {
        if(isspace(buffChar))
        {
            if(buffChar != '\n' && buffChar != '\r')
            {
                *pbuff++ = ' ';
            }
            while(isspace(buffChar))
            {
                buffChar = getc(fileInput);
            }
        }

        *pbuff++ = buffChar;
    }

    *pbuff = '\0';
}


void readRecordsFromFile(FILE *fileInput, List **listRecord)
{
    Citizen newRecord;
    char buff[BUFSIZ],
            *pSurname = buff,
            *pName,
            *pPatronymic,
            *pDataOfBirth,
            *pGender,
            *pSalary;

    while(!feof(fileInput))
    {
        readFromFile(fileInput, buff);

        pName = strchr(buff, ' ');
        *pName++ = '\0';

        pPatronymic = strchr(pName, ' ');
        *pPatronymic++ = '\0';

        pDataOfBirth = strchr(pPatronymic, ' ');
        *pDataOfBirth++ = '\0';

        pGender = strchr(pDataOfBirth, ' ');
        *pGender++ = '\0';

        pSalary = pGender + 1;
        *pSalary++ = '\0';

        strcpy(newRecord.name, pName);
        strcpy(newRecord.surname, pSurname);
        strcpy(newRecord.patronymic, pPatronymic);
        strcpy(newRecord.dataOfBirth, pDataOfBirth);
        newRecord.gender = *pGender;
        newRecord.salary = atoi(pSalary);

        pushRecord(listRecord, newRecord);
    }
}


int	compareDates(char *firstDate, char *secondDate)
{
    char *pFirstDate = firstDate + strlen(firstDate) - 4,
         *pSecondDate = secondDate + strlen(secondDate) - 4;

    int resultOfCompare;
    if((resultOfCompare = strcmp(pFirstDate, pSecondDate)) != 0)
    {
        return resultOfCompare;
    }

    pFirstDate = strchr(firstDate, '.');
    pSecondDate = strchr(secondDate, '.');

    if((resultOfCompare = strcmp(pFirstDate, pSecondDate)) != 0)
    {
        return resultOfCompare;
    }

    if((resultOfCompare = strcmp(firstDate, secondDate)) != 0)
    {
        return resultOfCompare;
    }

    return DATES_ARE_EQUAL;
    /*
    int i;

    i = 5;
    while (++i < 10)
        if (firstDate[i] != secondDate[i])
            return(firstDate[i] - secondDate[i]);
    i = 2;
    while (++i < 5)
        if (firstDate[i] != secondDate[i])
            return(firstDate[i] - secondDate[i]);
    i = -1;
    while (++i < 2)
        if (firstDate[i] != secondDate[i])
            return(firstDate[i] - secondDate[i]);
    return (0);

     */
}


void printList(List **headOfList)
{
    List *currentRecord = *headOfList;

    while(currentRecord != NULL)
    {
        printf("Фамилия: %s Имя: %s Отчество: %s Дата рождения:%s Пол: %c Заработная плата: %d\n", currentRecord->record.surname, currentRecord->record.name, currentRecord->record.patronymic, currentRecord->record.dataOfBirth, currentRecord->record.gender, currentRecord->record.salary);
        currentRecord = currentRecord->next;
    }
}


void removeRecord(List **listRecord, char *name)
{
    List *currentRecord;
    List *buff;

    if (*listRecord == NULL)
    {
        return ;
    }

    currentRecord = *listRecord;
    if (strcmp(name, currentRecord->record.name) == 0)
    {
        *listRecord = currentRecord->next;
        free(currentRecord);
    }
    else
    {
        while (currentRecord->next != NULL && strcmp(name, currentRecord->next->record.name) != 0)
        {
            currentRecord = currentRecord->next;
        }

        if(currentRecord->next == NULL)
        {
            return;
        }

        buff = currentRecord->next;
        currentRecord->next = currentRecord->next->next;
        free(buff);
    }
}

void freeList(List **headOfList)
{
    List *buff;

    while(*headOfList != NULL)
    {
        buff = (*headOfList)->next;
        free(*headOfList);
        *headOfList = buff;
    }
}

List *searchRecord(List **listRecord, char *name)
{
    List *currentRecord = *listRecord;

    while (currentRecord != NULL && strcmp(name, currentRecord->record.name) != 0)
    {
        currentRecord = currentRecord->next;
    }

    return currentRecord;
}

void pushRecord(List **headOfList, Citizen newRecord)
{
    List *currentRecord;
    List *newNode;

    if (*headOfList == NULL)
    {
        *headOfList = createList(newRecord);
        return ;
    }

    currentRecord = *headOfList;
    if (compareDates(currentRecord->record.dataOfBirth, newRecord.dataOfBirth) < 0)
    {
        newNode = createList(newRecord);
        newNode->next = currentRecord;
        *headOfList = newNode;
        return ;
    }

    while((currentRecord->next != NULL) &&
           compareDates(currentRecord->next->record.dataOfBirth, newRecord.dataOfBirth) > 0)
    {
        currentRecord = currentRecord->next;
    }

    newNode = createList(newRecord);
    newNode->next = currentRecord->next;
    currentRecord->next = newNode;
}


void copyRecord(Citizen *copyOfRecord, Citizen *sourceRecord)
{
    strcpy(copyOfRecord->name, sourceRecord->name);
    strcpy(copyOfRecord->surname, sourceRecord->surname);
    strcpy(copyOfRecord->patronymic, sourceRecord->patronymic);
    strcpy(copyOfRecord->dataOfBirth, sourceRecord->dataOfBirth);
    copyOfRecord->gender = sourceRecord->gender;
    copyOfRecord->salary = sourceRecord->salary;
}


void saveListInFile(List **listRecord)
{
    List *shift = *listRecord;
    FILE *fileOutput;

    fileOutput = fopen("save.txt", "w");
    while (shift)
    {
        fprintf(fileOutput, "%s %s %s %s %c %d\n", shift->record.surname, shift->record.name, shift->record.patronymic, shift->record.dataOfBirth, shift->record.gender, shift->record.salary);
        shift = shift->next;
    }
    fclose(fileOutput);
}

char *errors[] = {"Не было введено имя файла",
                  "Файла не существует"};

void error(int errorNumber)
{
    printf("Error: %s", errors[errorNumber]);
    exit(errorNumber);
}