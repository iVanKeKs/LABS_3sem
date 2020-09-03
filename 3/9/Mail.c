//
// Created by ivankeks on 02.12.2019.
//

#include "Mail.h"


Address *creatAddr(char *newAddr)
{
    Address *Addr = (Address *)malloc(sizeof(Address));
    char buff[BUFSIZ],
         *pbuff = buff,
         *pAddr = newAddr+0;

    while(!isspace(*pAddr))
    {
        *pbuff = *pAddr;
        ++pbuff;
        ++pAddr;
    }
    *pbuff = '\0';
    pbuff = buff;
    Addr->city = (char *)malloc(strlen(buff));
    strcpy(Addr->city, buff);

    ++pAddr;
    while(!isspace(*pAddr))
    {
        *pbuff = *pAddr;
        ++pbuff;
        ++pAddr;
    }
    *pbuff = '\0';
    pbuff = buff;
    Addr->street = (char *)malloc(strlen(buff));
    strcpy(Addr->street, buff);

    ++pAddr;
    while(!isspace(*pAddr))
    {
        *pbuff = *pAddr;
        ++pbuff;
        ++pAddr;
    }
    *pbuff = '\0';
    pbuff = buff;
    Addr->house = (char *)malloc(strlen(buff));
    strcpy(Addr->house, buff);

    ++pAddr;
    while(!isspace(*pAddr))
    {
        *pbuff = *pAddr;
        ++pbuff;
        ++pAddr;
    }
    *pbuff = '\0';
    pbuff = buff;
    Addr->apartment = (char *)malloc(strlen(buff));
    strcpy(Addr->apartment, buff);

    ++pAddr;
    while(!isspace(*pAddr))
    {
        *pbuff = *pAddr;
        ++pbuff;
        ++pAddr;
    }
    *pbuff = '\0';
    Addr->index = atoi(buff);

    return Addr;
}


Post *creatPost(char *newAddr)
{
    if(newAddr == NULL)
    {
        return NULL;
    }

    Post *newPost = (Post *)malloc(sizeof(Post));
    newPost->addr = creatAddr(newAddr);
    newPost->mails = NULL;

    return newPost;
}


Mail *creatMail(int weight, int mailID, char *newAddr)
{
    if(newAddr == NULL)
    {
        printf("Пустой адрес\n");
        return NULL;
    }
    Mail *newMail = (Mail *)malloc(sizeof(Mail));

    newMail->addr = creatAddr(newAddr);
    newMail->weight = weight;
    newMail->mailID = mailID;
    return newMail;
}

/*
int funcForComparison(Mail **mail1, Mail **mail2)
{

}
*/

void addMail(Post *post, int weight, int mailID, char *newAddr)
{
    if(post == NULL)
    {
        printf("Почта не создана");
        return;
    }

    Mail *newMail = creatMail(weight, mailID, newAddr);
    ++post->numberOfMails;
    post->mails = (Mail **)realloc(post->mails, sizeof(Mail *) * post->numberOfMails);
    post->mails[post->numberOfMails-1] = newMail;
}


void killAddr(Address *addr)
{
    free(addr->city);
    free(addr->street);
    free(addr->house);
    free(addr->apartment);
}


void deleteMail(Post *post, int mailID)
{
    int indexForDelete = 0,
        founded = 0;

    for(; indexForDelete < post->numberOfMails; ++indexForDelete)
    {
        if(post->mails[indexForDelete]->mailID == mailID)
        {
            founded = 1;
            break;
        }
    }

    if(!founded)
    {
        printf("Нет такой посылки\n");
        return;
    }

    killAddr(post->mails[indexForDelete]->addr);
    free(post->mails[indexForDelete]);
    post->mails[indexForDelete] = NULL;
    --post->numberOfMails;
    Mail **newMails = (Mail **)malloc(sizeof(Mail *) * post->numberOfMails),
         **pnew = newMails;

    for(int i = 0; i < post->numberOfMails+1; ++i)
    {
        if(i != indexForDelete)
        {
            *pnew = post->mails[i];
            ++pnew;
        }
    }

    free(post->mails);
    post->mails = newMails;
}


void printMail(Post *post, int mailID)
{
    if(post == NULL)
    {
        return;
    }

    for(int i = 0; i < post->numberOfMails; ++i)
    {
        if(post->mails[i]->mailID == mailID)
        {
            printf("Вес посылки: %d\n"
                   "Почтовый индефикатор: %d\n"
                   "Адрес доставки: %d г. %s, ул. %s, д. %s, кв. %s\n", post->mails[i]->weight, post->mails[i]->mailID,
                   post->mails[i]->addr->index, post->mails[i]->addr->city, post->mails[i]->addr->street,
                   post->mails[i]->addr->house, post->mails[i]->addr->apartment);
            return;
        }
    }

    printf("Посылка не найдена\n");
}


void printAll(Post *post)
{
    if(post == NULL)
    {
        printf("Почта не создана\n");
        return;
    }

    if(post->mails == NULL)
    {
        printf("Посылок нет\n");
        return;
    }

    for(int i = 0; i < post->numberOfMails; ++i)
    {
        printf("Вес посылки: %d\n"
               "Почтовый индефикатор: %d\n"
               "Адрес доставки: %d г. %s, ул. %s, д. %s, кв. %s\n", post->mails[i]->weight, post->mails[i]->mailID,
               post->mails[i]->addr->index, post->mails[i]->addr->city, post->mails[i]->addr->street,
               post->mails[i]->addr->house, post->mails[i]->addr->apartment);
    }
}


void killPost(Post *post)
{
    if(post == NULL)
    {
        return;
    }

    killAddr(post->addr);

    for(int i = 0; i < post->numberOfMails; ++i)
    {
        killAddr(post->mails[i]->addr);
        free(post->mails[i]);
    }

    free(post);
}