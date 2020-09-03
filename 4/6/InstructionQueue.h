//
// Created by iVan on 24.08.2020.
//

#ifndef INC_6_INSTRUCTIONQUEUE_H
#define INC_6_INSTRUCTIONQUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define END_OF_LIST 0
#define TRUE 1

typedef struct __nodeOfList Node;
typedef struct __list SingleLinkedList;

struct __nodeOfList
{
    char *data;
    Node *next;
};

struct __list
{
    Node *head;
    int size;
};

//SingleLinkedList *createNewList();

Node *createNewNode(char *textOfNewInstruction);
void Push(SingleLinkedList *headList, char *textOfNewInstruction);
void deleteNode(SingleLinkedList *headList);
void deleteNumberOfNodes(SingleLinkedList *headList, int numberOfDelete);
int Dequeue(SingleLinkedList *headList, char *outputString);
void saveList(SingleLinkedList *headList);
void freeList(SingleLinkedList *headList);

#endif //INC_6_INSTRUCTIONQUEUE_H