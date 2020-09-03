//
// Created by iVan on 03.11.2019.
//

#ifndef INC_12312312313_LIST_H
#define INC_12312312313_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct _list list;
typedef struct _node node;

// Односвязанный список
struct _list
{
    // Начало списка
    node *head;
    // Размер списка
    int size;
};

// Эллемент списка
struct _node
{
    // Значение хранимое эллементом
    int data;
    // Казатель на следующий элемент
    node *next;
};

// Создать пустой список
list *createlist();

// Глубокое копирование
list* copylist(list*);

// Добавить элемент в конец списка
void addNode(list *, int );

// Удалить список
void deletelist(list *);

// Удаляет элемент на позиции
void deletel(list *, int);

// Посмотреть эллемент на позиции
int lookEl(list *, int);

// Меняет значение на позиции
void changeData(list *, int, int);

// Вывод списка
void printlist(list *List);

#endif //INC_12312312313_LIST_H
