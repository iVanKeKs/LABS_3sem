//
// Created by iVan on 10.07.2020.
//

#include "LIFOchar.h"

void PushChar(CharLIFO **headLIFO, char letter)
{
    CharLIFO *newNode;

    newNode = (CharLIFO*)malloc(sizeof(CharLIFO));
    newNode->data = letter;
	if (*headLIFO == NULL)
	{
        newNode->next = NULL;
		*headLIFO = newNode;
	}
	else
    {
        newNode->next = *headLIFO;
        *headLIFO = newNode;
    }
}

char PopChar(CharLIFO **headLIFO)
{
	char data;
    CharLIFO *buff;

	if (*headLIFO == NULL)
    {
        return ('\0');
    }

	data = (*headLIFO)->data;
    buff = *headLIFO;
	*headLIFO = (*headLIFO)->next;
	free(buff);
	return data;
}