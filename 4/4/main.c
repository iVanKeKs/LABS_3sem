
#include "SomeTown.h"

int main(int argc, char **argv)
{
    if(argc == LENGTH_WITHOUT_FILES)
    {
        error(ERROR_NO_FILES_IN_ARGS);
    }

	FILE *fileInput;
	List *listRecord = NULL;
	List *someRecord;

	if (!(fileInput = fopen(argv[1], "r")))
    {
	    error(ERROR_FILE_NOT_EXIST);
    }

    readRecordsFromFile(fileInput, &listRecord);
    printList(&listRecord);

    someRecord = searchRecord(&listRecord, "Test2");
	printf("%s %s\n", someRecord->record.name, someRecord->record.surname);

	removeRecord(&listRecord, "Test2");
    printList(&listRecord);
    saveListInFile(&listRecord);

    freeList(&listRecord);
	fclose(fileInput);
}