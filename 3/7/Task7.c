//
// Created by ivankeks on 02.12.2019.
//

#include "String.h"

void lab7()
{
    String *str1, *str2, *str3;

    char buff[BUFSIZ];
    scanf("%s", buff);

    str1 = creatString(buff);
    str3 = creatString(NULL);
    printf("str1: %d %s\n", str1->sizeOfString, str1->data);

    str2 = copyString(str1);
    printf("str2: %d %s\n", str2->sizeOfString, str2->data);
    printf("str3: %d %s\n", str3->sizeOfString, str3->data);

    int cmp = cmpStrings(str1, str2);
    printf("%d\n", cmp);
    cmp = cmpStrings(str1, str3);
    printf("%d\n", cmp);

    cntStrings(str1, str2);

    printf("%d %s\n", str2->sizeOfString, str2->data);

    killString(str1);
    killString(str2);
    killString(str3);
}