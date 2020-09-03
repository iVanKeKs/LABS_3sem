//
// Created by ivankeks on 26.06.2020.
//

#include "ManWithBoat.h"

char *errors[] = {"Не был передан входной файл\n",
                  "Входной файл не существует\n",
                  "Команда не найдена\n",
                  "В лодке никого нет\n",
                  "В лодке уже кто-то есть\n",
                  "Такого груза не существует\n",
                  "Такого груза на берегу нет\n",
                  "Вы оставили козу с капустой\n",
                  "Вы оставили волка с козой\n"};

void error(int errorId)
{
    printf("Error: %s", errors[-1-errorId]);
    exit(errorId);
}

void initboat(Boat *newBoat)
{
    newBoat->side = SIDE_LEFT;
    newBoat->who = NULL;
}

void initsides(Sides *leftSide, Sides *rightSide)
{
    leftSide->hereCabbage = CABBAGE;
    leftSide->hereGoat = GOAT;
    leftSide->hereWolf = WOLF;

    rightSide->hereCabbage = NULL;
    rightSide->hereGoat = NULL;
    rightSide->hereWolf = NULL;
}

void read(FILE *fIn, char *buff)
{
    char symbol;
    while((symbol = fgetc(fIn)) != '\n' && symbol != EOF)
    {
        *buff = symbol;
        ++buff;
    }
    *buff = '\0';
}

void put(Boat *manOnBoat, Sides *currentSide)
{
    switch(manOnBoat->who)
    {
        case(CABBAGE):
        {
            currentSide->hereCabbage = CABBAGE;
            printf("Вы высадили капусту\n");
            break;
        }

        case(GOAT):
        {
            currentSide->hereGoat = GOAT;
            printf("Вы высадили козу\n");
            break;
        }

        case(WOLF):
        {
            currentSide->hereWolf = WOLF;
            printf("Вы высадили волка\n");
        }
    }

    manOnBoat->who = NULL;
}

void take(Boat *manOnBoat, Sides *currentSide, int who)
{
    switch(who)
    {
        case(CABBAGE):
        {
            if(currentSide->hereCabbage != NULL)
            {
                currentSide->hereCabbage = NULL;
                printf("Вы подобрали капусту\n");
                break;
            }
            else
            {
                error(ERROR_CARGO_NOT_ON_SIDE);
            }
        }

        case(GOAT):
        {
            if(currentSide->hereGoat != NULL)
            {
                currentSide->hereGoat = NULL;
                printf("Вы подобрали козу\n");
                break;
            }
            else
            {
                error(ERROR_CARGO_NOT_ON_SIDE);
            }
        }

        case(WOLF):
        {
            if(currentSide->hereWolf != NULL)
            {
                currentSide->hereWolf = NULL;
                printf("Вы подобрали волка\n");
                break;
            }
            else
            {
                error(ERROR_CARGO_NOT_ON_SIDE);
            }
        }
    }

    manOnBoat->who = who;
}

void movingtest(Sides *currentSide)
{
    if(currentSide->hereGoat != NULL && currentSide->hereCabbage != NULL)
    {
        error(ERROR_GOAT_WITH_CABBAGE);
    }
    else if(currentSide->hereGoat != NULL && currentSide->hereWolf)
    {
        error(ERROR_WOLF_WITH_GOAT);
    }
}