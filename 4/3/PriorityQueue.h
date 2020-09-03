//
// Created by iVan on 17.08.2020.
//

#ifndef INC_3_PRIORITYQUEUE_H
#define INC_3_PRIORITYQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct __singlyLinkedList listWithPriority;

struct __singlyLinkedList
{
    struct __singlyLinkedList *next;
    int priority;
    char *data;
};

void readFromFile(FILE *fileInput, char *buff);
void parseInputString(listWithPriority **headOfList, char *inputString);

listWithPriority *CreateNewNode(int priority, char *data);
void EnqueuePriority(listWithPriority **headOfList, int priority, char *task);
void Enqueue(listWithPriority **headOfList, int priority, char *task);
void Dequeue(listWithPriority **headOfList, char *outputString);
void printList(listWithPriority *headOfList);
void freeList(listWithPriority **headOfList);

#endif //INC_3_PRIORITYQUEUE_H
