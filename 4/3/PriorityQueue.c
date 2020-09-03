//
// Created by iVan on 17.08.2020.
//

#include "PriorityQueue.h"

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

        *pbuff++ = tolower(buffChar);
    }

    *pbuff = '\0';
}

listWithPriority *CreateNewNode(int priority, char *data)
{
    listWithPriority *newNode = (listWithPriority*)malloc(sizeof(listWithPriority));

    newNode->next = NULL;
    newNode->priority = priority;

    newNode->data = (char*)malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(newNode->data, data);

    return newNode;
}

void Enqueue(listWithPriority **headOfList, int priority, char *task)
{
    listWithPriority *newNode = CreateNewNode(priority, task);
    listWithPriority *currentNode;

    currentNode = *headOfList;
    if (currentNode == NULL)
    {
        *headOfList = newNode;
        return;
    }

    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;
}

void Dequeue(listWithPriority **headOfList, char *outputString)
{
    listWithPriority *buff;

    buff = *headOfList;
    if (buff == NULL)
    {
        *outputString = '\0';
    }

    *headOfList = (*headOfList)->next;
    strcpy(outputString, buff->data);

    free(buff->data);
    free(buff);
}

void EnqueuePriority(listWithPriority **headOfList, int priority, char *task)
{
    listWithPriority *newNode = CreateNewNode(priority, task);;

    if (*headOfList == NULL)
    {
        *headOfList = newNode;
        return;
    }

    listWithPriority *currentNode = *headOfList;
    if (newNode->priority < currentNode->priority)
    {
        newNode->next = *headOfList;
        *headOfList = newNode;
    }
    while (currentNode->next && currentNode->next->priority < newNode->priority)
    {
        currentNode = currentNode->next;
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

void parseInputString(listWithPriority **headOfList, char *inputString)
{
    int priority = 0;

    char *priorityStr = strchr(inputString, '='),
         *pstr;

    ++priorityStr;

    pstr = strchr(priorityStr, ' ');
    *pstr++ = '\0';

    priority = atoi(priorityStr);

    pstr = strchr(pstr, '\"');

    EnqueuePriority(headOfList, priority, pstr);
}

void printList(listWithPriority *headOfList)
{
    while(headOfList != NULL)
    {
        printf("%d %s\n", headOfList->priority, headOfList->data);
        headOfList = headOfList->next;
    }
}

void freeList(listWithPriority **headOfList)
{
    listWithPriority *buff;

    while(*headOfList != NULL)
    {
        buff = (*headOfList)->next;
        free((*headOfList)->data);
        free(*headOfList);
        *headOfList = buff;
    }
}

//char *errors[] = {"Не введенны имена файлов",
//                  "Такого файла не существует"};
//
//void error(int numberOfError, listWithPriority **headOfList)
//{
//    printf("Error: %s", errors[numberOfError-1]);
//
//    freeList(headOfList);
//    exit(numberOfError);
//}
