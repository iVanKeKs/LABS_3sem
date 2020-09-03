#include "PriorityQueue.h"

int main(int argc, char **argv)
{
//    if(argc == LENGTH_WITHOUT_FILES)
//    {
//        error(ERROR_ARGUMENTS_IS_EMPTY, NULL);
//    }

	FILE *fileInput;
    listWithPriority *headOfQueue = NULL;
	char buff[BUFSIZ];
	char *pbuff = buff,
	     nameOfInputFile[BUFSIZ];

	scanf("%s", nameOfInputFile);
	while(strcmp(nameOfInputFile, "END") != 0)
    {
        if(!(fileInput = fopen(nameOfInputFile, "r")))
        {
            printf("Файл \"%s\" не существует\n", nameOfInputFile);
        }
        else
        {
            while (!feof(fileInput))
            {
                readFromFile(fileInput, buff);
                parseInputString(&headOfQueue, pbuff);
            }

            fclose(fileInput);
        }

        scanf("%s", nameOfInputFile);
    }

    printList(headOfQueue);

    char test[BUFSIZ];
    Dequeue(&headOfQueue, test);
    printf("%s\n", test);

    Enqueue(&headOfQueue, 1, "asdf");
    printList(headOfQueue);

    freeList(&headOfQueue);
}