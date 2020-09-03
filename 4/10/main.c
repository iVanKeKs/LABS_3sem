#include "ArithmeticBinaryTree.h"


int main(int argc, char **argv)
{
    if(argc == 1)
    {
        printf("Не был получен входной файл\n");
        exit(-1);
    }

	FILE *fileInput;

	if(!(fileInput = fopen(argv[1], "r")))
	{
		printf("Входного файла не существует\n");
		exit(-1);
	}

	CalculateBinaryExpression(fileInput);

	fclose(fileInput);
	return 0;
}