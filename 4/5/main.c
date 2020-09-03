#include "TextParser.h"

int main(int argc, char **argv)
{
    if(argc == LENGTH_WITHOUT_FILE)
    {
        printf("Error: не было получено имя файла\n");
        exit(-1);
    }

	FILE *fileInput;

	char buff[30],
	     *pbuff = buff,
	     buffChar;

	Tree *newTree = NULL,
	     *tree = NULL,
	     *tree1 = NULL;

	int number = 25;

	char shortestString[BUFSIZ],
	     longestString[BUFSIZ];

	StrWithLen nodeMinLength, nodeMaxLength;

	if (!(fileInput = fopen(argv[1], "r")))
    {
	    printf("Error: Такого файла не существует\n");
	    exit(-1);
    }

	while (!feof(fileInput))
	{
        buffChar = fgetc(fileInput);

		if (!isspace(buffChar) && buffChar != EOF)
        {
		    *pbuff++ = buffChar;
        }
		else if (pbuff != buff)
		{
			*pbuff = '\0';
            insertNewNode(&tree, buff);
            pbuff = buff;
		}
	}

    printTree(tree, 0);

    swapTree(tree, &newTree);
    printTree(newTree, 0);

    printLongestStrings(newTree, &number);

    printf("%d\n", calculateDeepOfTree(newTree));

    nodeMinLength.length = nodeMaxLength.length = strlen(newTree->data);
    nodeMinLength.data = nodeMaxLength.data = newTree->data;

    searchLongNode(newTree, longestString);
    searchShortNode(newTree, shortestString);

    printf("%s %s\n", nodeMinLength.data, nodeMaxLength.data);
    saveTree(newTree);

	FILE *fileInput1;

	if (!(fileInput1 = fopen("save.txt", "r")))
	{
		exit(-1);
	}

    tree1 = loadTree(tree1, fileInput1);
    printTree(tree1, 0);

    freeTree(tree1);
    freeTree(newTree);
}