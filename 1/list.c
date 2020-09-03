//
// Created by iVan on 04.11.2019.
//

#include "List.h"

//Создать список
list *createlist()
{
    list *newList;

    if((newList = (list*)malloc(sizeof(list))) == NULL)
    {
        perror("Не удалось выделить память под новый список");
        return NULL;
    }
    newList->size = 0;
    newList->head = NULL;

    return newList;
}


//Создать эллемент списка
node *creatnode(int Data)
{
    node *newNode;

    if((newNode = (node*)malloc(sizeof(node))) == NULL)
    {
        perror("Не удалось выделить память под новый элемент списка");
        return NULL;
    }
    newNode->data = Data;
    newNode->next = NULL;

    return newNode;
}


//Добавить значение на позицию
void addNode(list *List, int NodeData)
{
    //Если принесен не реализованный список
    if(List == NULL)
    {
        printf("Полученный список пуст\n");
        return;
    }

    node *tmp = List->head;

    //Если список не пустой
    if(List->head != NULL)
    {
        for(int i = 1; i != List->size; ++i)
        {
            tmp = tmp->next;
        }
    }
    //Вставка первого элемента в список
    else
    {
        List->head = creatnode(NodeData);
        List->size = 1;
        return;
    }

    //Ставим эллемент в список
    node *newNode = creatnode(NodeData);
    tmp->next = newNode;
    ++(List->size);
}


//Удалаят список
void deletelist(list *List)
{
    //Список не реализован
    if(!(List))
    {
        return;
    }

    //Список не пустой
    if(List->head != NULL)
    {
        node *tmp;
        while(List->head->next != NULL)
        {
            tmp = List->head;
            List->head = List->head->next;
            free(tmp);
        }
        free(List->head);
    }

    free(List);
}


void deletel(list *List, int position)
{
    if(List == NULL)
    {
        printf("Список не реализован");
        return;
    }

    if(List->head == NULL)
    {
        printf("Список пустой");
        return;
    }

    if(List->size < position)
    {
        printf("Список содержит меньше эллементов");
        return;
    }

    //Текущий эллемент в переборе
    node *tmp = List->head;
    if(position == 1)
    {
        List->head = List->head->next;
        --(List->size);
        free(tmp);
        return;
    }

    for(int i = 1; i != position-1; ++i)
    {
        tmp = tmp->next;
    }

    //Эллемент который мы хотим удалить
    node *buff = tmp->next;
    tmp->next = buff->next;
    --(List->size);
    free(buff);
}


int lookEl(list *List, int position)
{
    if(List == NULL)
    {
        printf("Список не реализован");
        return NULL;
    }

    if(List->head == NULL)
    {
        printf("Список пустой");
        return NULL;
    }

    if(List->size < position)
    {
        printf("Список меньше указанной позиции");
        return NULL;
    }

    node *tmp = List->head;
    for(int i = 1; i!=position; ++i)
    {
        tmp = tmp->next;
    }
    return tmp->data;
}


list *copylist(list *sourceList)
{
    if(sourceList == NULL)
    {
        printf("Список не реализован\n");
        return NULL;
    }

    list *newList = createlist();

    if(sourceList->head == NULL)
    {
        return newList;
    }

    node *tmp = sourceList->head;

    while(tmp != NULL)
    {
        addNode(newList, tmp->data);
        tmp = tmp->next;
    }
    return newList;
}


void changeData(list *List, int newData, int position)
{
    if(List == NULL)
    {
        printf("Список не реализован");
        return;
    }

    if(List->head == NULL)
    {
        printf("Список пустой");
        return;
    }

    if(List->size < position)
    {
        printf("Список содержит меньше эллементов");
        return;
    }

    node *tmp = List->head;

    for(int i = 1; i < position; ++i)
    {
        tmp = tmp->next;
    }

    tmp->data = newData;
}


void printlist(list *List)
{
    node *tmp = List->head;
    while(tmp)
    {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
}