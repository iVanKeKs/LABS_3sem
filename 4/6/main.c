#include "InstructionQueue.h"

int main()
{
	char buff[BUFSIZ];
	SingleLinkedList list;

	list.head = NULL;
	list.size = 0;

	while (TRUE)
	{
		scanf("%s", buff);

		if (strstr(buff, "STOP"))
        {
		    break ;
        }

        Push(&list, buff);
	}

    deleteNumberOfNodes(&list, list.size / 2);
    saveList(&list);
    freeList(&list);
}