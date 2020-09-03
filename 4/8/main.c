

#include "HashTable.h"


int main(int argc, char **argv)
{
    if(argc == 1)
    {
        printf("Error: Не был пролучен входной файл\n");
        exit(-1);
    }

	list *hashTable[HASHSIZE] = {NULL};
	FILE *fileInput;

	if (!(fileInput = fopen(argv[1], "r")))
    {
	    printf("Error: Такого файла не существует\n");
	    exit(-1);
    }

    readFromFileAndParse(hashTable, fileInput);
    freeArrayOfList(hashTable);
}