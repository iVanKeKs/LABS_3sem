//
// Created by ivankeks on 29.11.2019.
//

#include <string.h>

#include "Message.h"

void lab4()
{
    Message *buffMessage;

    char buff[BUFSIZ];
    int numberOfMessage = 0,
        sizeOfMessage;

    FILE *fout;
    if(!(fout = fopen("outBuff.txt", "w")))
    {
        perror("file out");
        exit(-1);
    }

    while(1)
    {
        gets(buff);

        if(!strcmp(buff, "stop"))
        {
            break;
        }

        if(numberOfMessage != 0)
        {
            fprintf(fout, "\n");
        }

        ++numberOfMessage;
        sizeOfMessage = strlen(buff);
        buffMessage = creatMessage(buff, numberOfMessage, sizeOfMessage);
        printToFile(fout, buffMessage);
        killMessage(buffMessage);
    }

    Message **massOfMessage = (Message **)malloc(sizeof(Message *)*numberOfMessage);

    fclose(fout);
    if(!(fout = fopen("outBuff.txt", "r")))
    {
        perror("file out");
        free(massOfMessage);
        exit(-1);
    }

    numberOfMessage = 0;
    while(1)
    {
        buffMessage = (Message *)malloc(sizeof(Message));
        if(readNextMessage(fout, buffMessage) == -1)
        {
            free(buffMessage);
            break;
        }
        ++numberOfMessage;
        massOfMessage = (Message **)realloc(massOfMessage, numberOfMessage * sizeof(Message*));
        massOfMessage[numberOfMessage-1] = buffMessage;
        printf("%d %d %s\n", buffMessage->id,
                                    buffMessage->sizeOfMessage,
                                    buffMessage->textOfMessage);
    }

    killMassMessage(massOfMessage, numberOfMessage);
}