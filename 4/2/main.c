#include "MemoryCell.h"

#define BUFF_SIZE 30

int main(int argc, char **argv)
{
	FILE *fileInput;

	if (!(fileInput = fopen(argv[1], "r")))
    {
	    error(ERROR_FILE_NOT_EXIST, NULL);
    }

    ArrayOfVariables varArray;
    char buff[BUFF_SIZE];

    varArray.size = 0;
	while (!feof(fileInput))
    {
        readFromFile(fileInput, buff);
        defineOperation(&varArray, buff);
    }

    freeArrayOfVariables(&varArray);
}