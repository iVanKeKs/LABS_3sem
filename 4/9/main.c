
#include "BracketTree.h"

int	main(int argc, char **argv)
{
    if(argc == 1)
    {
        printf("Не получен входной файл\n");
        exit(-1);
    }

	FILE *fileInput;


	if (!(fileInput = fopen(argv[1], "r")))
    {
	    printf("%s - такого файла не существует", argv[1]);
	    exit(-1);
    }

    BracketTree *tree = NULL;

    char buff[BUFSIZ];

	while (!feof(fileInput))
	{
        readFromFile(fileInput, buff);

        parseInputString(buff, &tree);
        printTree(tree, 0);
		printf("\n");
        freeTree(tree);
		free(tree);

        tree = NULL;
	}

	fclose(fileInput);
}