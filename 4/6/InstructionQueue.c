//
// Created by iVan on 24.08.2020.
//

#include "InstructionQueue.h"

Node *createNewNode(char *textOfNewInstruction)
{
    Node *newMode;

    newMode = (Node*)malloc(sizeof(Node));

    newMode->next = NULL;
    newMode->data = (char*)malloc(sizeof(char) * (strlen(textOfNewInstruction) + 1));
    strcpy(newMode->data, textOfNewInstruction);

    return newMode;
}

void Push(SingleLinkedList *headList, char *textOfNewInstruction)
{
    if(headList == NULL)
    {
        return;
    }

    Node *newNode = createNewNode(textOfNewInstruction);

    headList->size++;

    newNode->next = headList->head;
    headList->head = newNode;
}

void deleteNode(SingleLinkedList *headList)
{
    if (headList->head == NULL)
    {
        return ;
    }

    Node *deletingNode;

    headList->size--;

    deletingNode = headList->head;
    headList->head = headList->head->next;

    free(deletingNode->data);
    free(deletingNode);
}

void deleteNumberOfNodes(SingleLinkedList *headList, int numberOfDelete)
{
    for (int i = 0; i < numberOfDelete; ++i)
    {
        deleteNode(headList);
    }
}

int Dequeue(SingleLinkedList *headList, char *outputString)
{
    if (headList->head == NULL)
    {
        return END_OF_LIST;
    }

    Node *currentNode = headList->head;

    if (currentNode->next == NULL)
    {
        strcpy(outputString, currentNode->data);
        free(currentNode);
        headList->head = NULL;

        return !END_OF_LIST;
    }

    while (currentNode->next->next != NULL)
    {
        currentNode = currentNode->next;
    }

    strcpy(outputString, currentNode->data);
    free(currentNode->next);
    currentNode->next = NULL;

    return !END_OF_LIST;
}

void saveList(SingleLinkedList *headList)
{
    FILE *fileOutput;
    char buff[BUFSIZ];

    fileOutput = fopen("save.txt", "w");

    while(Dequeue(headList, buff) != NULL)
    {
        fprintf(fileOutput, "%s\n", buff);
    }

    fclose(fileOutput);
}

void freeList(SingleLinkedList *headList)
{
    if(headList == NULL || headList->head == NULL)
    {
        return;
    }

    Node *buff;
    while(headList->head != NULL)
    {
        buff = headList->head;
        headList->head = headList->head->next;
        free(buff->data);
        free(buff);
    }

    headList->size = 0;
}