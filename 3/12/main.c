#include "ReversePolishNotatio.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        printf("Нет входных файлов\n");
        exit(-1);
    }

	FILE *fileInput,
	     *fileOutput;

    char buff[BUFF_SIZE],
	     errorFileName[BUFF_SIZE];

	int result,
        numberOfExpression;
	for (int numberOfFile = 1; numberOfFile < argc; ++numberOfFile)
	{
		if (!(fileInput = fopen(argv[numberOfFile], "r")))
		{
			printf("Входной файл %s не удалось открыть\n", argv[numberOfFile]);
			continue;
		}

        strcpy(errorFileName, "errors_");
		strcat(errorFileName, argv[numberOfFile]);
		if (!(fileOutput = fopen(errorFileName, "w")))
		{
			printf("Выходной файл %s не удалось создать или открыть\n", errorFileName);
			continue;
		}
		printf("Файл вывода ошибок %s\n", errorFileName);

        numberOfExpression = 1;
		while(!feof(fileInput))
		{
		    readToBuff(buff, fileInput);
			if (ExpressionCalculation(buff, &result))
            {
                printf("%s = %d\n", buff, result);
            }
			else
            {
                fprintf(fileOutput, "Сторака номер %d\n%s\n\n", numberOfExpression, buff);
            }
            numberOfExpression++;
		}

        fclose(fileOutput);
        fclose(fileInput);
	}

	return 0;
}
