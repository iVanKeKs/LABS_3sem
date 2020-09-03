//
// Created by iVan on 20.02.2020.
//

//   №17
//Схема Горнера
int Gorner(char *sourceNumber, int countSystem)
{
    char *b = sourceNumber;
    int result = 0;

    while(*b)
    {                                  /*Если число        АSCII-код 0 */
        result = result * countSystem + (isdigit(*b) ? (*b++ - '0') : (toupper(*b++) - 'A' + 10));
    }

    //printf("%s -> %d | cc %d", sourceNumber, result, countSystem);

    return result;
}