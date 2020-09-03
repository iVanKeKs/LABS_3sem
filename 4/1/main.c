
#include "ArrayInterpreter.h"

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        error(ERROR_COMMAND_LINE_PARAMETERS);
    }

	FILE *fileInput /*, *f_array*/;
	char buff[BUFSIZ];

	if (!(fileInput = fopen(argv[1], "r")))
    {
        error(ERROR_FILE_NOT_EXIST);
    }

	while(!feof(fileInput))
    {
        readFromFile(fileInput, buff);
        searchAndExeOperation(buff);
    }

    return 0;
}