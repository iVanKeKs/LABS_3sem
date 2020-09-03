//
// Created by ivankeks on 02.12.2019.
//

#ifndef LAB3_MAIL_H
#define LAB3_MAIL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct __mail Mail;
typedef struct __address Address;
typedef struct __post Post;

struct __address
{
    char *city;
    char *street;
    char *house;
    char *apartment;
    int index;
};

struct __mail
{
    int weight;
    int mailID;
    struct __address *addr;
};


struct __post
{
    struct __address *addr;
    struct __mail **mails;
    int numberOfMails;
};


// Создать новую почту
Post *creatPost(char *);

// Создать новое письмо
void addMail(Post *, int , int , char *);

// Распечатать инфо о письме
void printMail(Post *, int );

void printAll(Post *);

// Удаление почты
void killPost(Post *);

// Удаление почты по индексу
void deleteMail(Post *, int );

#endif //LAB3_MAIL_H