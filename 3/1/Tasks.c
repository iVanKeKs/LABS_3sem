//
// Created by ivankeks on 21.11.2019.
//

#include "Tasks.h"

// Перевод из
void lab1(const unsigned int number, int powerCountSystem)
{
    if(powerCountSystem > 5)
    {
        printf("Не верно указана степень\n");
        exit(-1);
    }

    char res[BUFSIZ],
         *pres = res + BUFSIZ - 1;
         *pres-- = '\0';

    unsigned int buffres;
    int mask = pow(2, powerCountSystem) - 1,
        numBuf = number;

    while(numBuf)
    {
        buffres = numBuf & mask;
        if(buffres < 9)
        {
            *pres = buffres + '0';
        }
        else
        {
            *pres = buffres - 10 + 'A';
        }
        numBuf = numBuf >> (powerCountSystem);
        --pres;
    }

    printf("X_10 = %d\nX_%d = %s\n", number, mask+1, ++pres);
}