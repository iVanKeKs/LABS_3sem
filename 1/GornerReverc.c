//
// Created by iVan on 20.02.2020.
//

//   №17
// Обратная схема Горнера
void GornerReverce(int sourceNumber, int countSystem)
{
    const char size = 100;

    int buffNumber = sourceNumber,
            sizeOfResult = 0;
    char letterBuff;
    char outputBuf[size];
    char *b = outputBuf + size - 1;
    b--;

    outputBuf[size-1] = '\0';

    while(buffNumber)
    {
        if((letterBuff = buffNumber % countSystem) < 10)
        {//               ASCII код 0
            *b-- = letterBuff + '0';
        }
        else
        {//                    ASCII код А
            *b-- = letterBuff - 10 + 'A';
        }
        buffNumber /= countSystem;
        ++sizeOfResult;
    }

    printf("%s\n", ++b);
}