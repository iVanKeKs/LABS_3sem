//
// Created by ivankeks on 26.06.2020.
//

#ifndef LAB3_11_MANWITHBOAT_H
#define LAB3_11_MANWITHBOAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CABBAGE 1
#define GOAT CABBAGE + 1
#define WOLF GOAT + 1

#define SIDE_LEFT WOLF + 1
#define SIDE_RIGHT SIDE_LEFT + 1

typedef struct _boat Boat;
typedef struct _sides Sides;

//Структура лодки с мужиком
struct  _boat
{
    int who;    //Кто сейчас в лодке
    int side;   //На какой стороне находится лодка
};

//Структура берегов
struct _sides
{
    int hereCabbage; //Есть ли на берегу капуста
    int hereGoat;    //Есть ли на берегу коза
    int hereWolf;    //Есть ли на берегу волк
};

//Заполнение полей структуры лодки
void initboat(Boat *);

//Заполнение полей структур сторон реки
void initsides(Sides *, Sides *);

//Читате команду из файла
void read(FILE *,char *);

//Высаживает груз на берег
void put(Boat *, Sides *);

//Забиает груз с берега
void take(Boat *, Sides *, int);

void movingtest(Sides *);

//Возможные ошибки
#define ERROR_FILE_NOT_FOUND -1
#define ERROR_FILE_NOT_EXIST ERROR_FILE_NOT_FOUND - 1
#define ERROR_COMMAND_NOT_FOUND ERROR_FILE_NOT_EXIST - 1
#define ERROR_NOONE_IN_BOAT ERROR_COMMAND_NOT_FOUND - 1
#define ERROR_SOMEONE_IN_BOAT ERROR_NOONE_IN_BOAT - 1
#define ERROR_CARGO_NOT_EXIST ERROR_SOMEONE_IN_BOAT - 1
#define ERROR_CARGO_NOT_ON_SIDE ERROR_CARGO_NOT_EXIST - 1
#define ERROR_GOAT_WITH_CABBAGE ERROR_CARGO_NOT_ON_SIDE - 1
#define ERROR_WOLF_WITH_GOAT ERROR_GOAT_WITH_CABBAGE - 1

void error(int);

#endif //LAB3_11_MANWITHBOAT_H
