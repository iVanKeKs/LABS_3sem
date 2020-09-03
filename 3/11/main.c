#include "ManWithBoat.h"

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        error(ERROR_FILE_NOT_FOUND);
    }

    FILE *fIn;
    if((fIn = fopen(argv[1], "r")) == NULL)
    {
        error(ERROR_FILE_NOT_EXIST);
    }

    Boat manOnBoat;
    Sides leftSide, rightSide;
    initboat(&manOnBoat);
    initsides(&leftSide, &rightSide);

    char buff[13],
         *pbuff,
         command[5],
         *pcommand;

    while(!feof(fIn))
    {
        read(fIn, buff);
        pbuff = buff;
        pcommand = command;
        while(*pbuff != ' ' && *pbuff != '\0')
        {
            *pcommand = *pbuff;
            ++pbuff;
            ++pcommand;
        }
        ++pbuff;
        *pcommand = '\0';

        if((strcmp(command, "move")) == 0)
        {
            if(manOnBoat.side == SIDE_LEFT)
            {
                movingtest(&leftSide);
                manOnBoat.side = SIDE_RIGHT;
                printf("Вы переплыли на правую сторону\n");
            }
            else
            {
                movingtest(&rightSide);
                manOnBoat.side = SIDE_LEFT;
                printf("Вы переплыли на левую сторону\n");
            }
        }

        else if((strcmp(command, "take")) == 0)
        {
            if(manOnBoat.who == NULL)
            {
                //Кого нужно подобрать
                int who = NULL;
                if((strcmp(pbuff, "cabbage")) == 0)
                {
                    who = CABBAGE;
                }
                else if((strcmp(pbuff, "goat")) == 0)
                {
                    who = GOAT;
                }
                else if((strcmp(pbuff, "wolf")) == 0)
                {
                    who = WOLF;
                }
                else
                {
                    error(ERROR_CARGO_NOT_EXIST);
                }

                if(manOnBoat.side == SIDE_LEFT)
                {
                    printf("\n");
                    take(&manOnBoat, &leftSide, who);
                }
                else
                {
                    take(&manOnBoat, &rightSide, who);
                }
            }
            else
            {
                error(ERROR_SOMEONE_IN_BOAT);
            }
        }

        else if((strcmp(command, "put")) == 0)
        {
            if(manOnBoat.who != NULL)
            {
                if(manOnBoat.side == SIDE_LEFT)
                {
                    put(&manOnBoat, &leftSide);
                }
                else
                {
                    put(&manOnBoat, &rightSide);
                }
            }
            else
            {
                error(ERROR_NOONE_IN_BOAT);
            }
        }
        else
        {
            error(ERROR_COMMAND_NOT_FOUND);
        }

        if(rightSide.hereCabbage != NULL &&
           rightSide.hereGoat != NULL &&
           rightSide.hereWolf != NULL)
        {
            printf("Вы перевезли всех на другой берег!\n");
            break;
        }
    }
    return 0;
}