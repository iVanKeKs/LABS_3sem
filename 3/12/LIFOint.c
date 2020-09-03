//
// Created by iVan on 10.07.2020.
//

#include "LIFOint.h"

void PushInt(IntLIFO **headLIFO, int data)
{
    IntLIFO	*newNode;

    newNode = (IntLIFO*)malloc(sizeof(IntLIFO));
    newNode->data = data;
	if (*headLIFO == NULL)
	{
        newNode->next = NULL;
		*headLIFO = newNode;
		return ;
	}
    newNode->next = *headLIFO;
	*headLIFO = newNode;
}

int	PopInt(IntLIFO **headLIFO)
{
	int	data;
    IntLIFO	*buff;

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

int	intLIFOSize(IntLIFO *head)
{
	int size = 0;
	while(head != NULL)
	{
		++size;
        head = head->next;
	}
	return size;
}
