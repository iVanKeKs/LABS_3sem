
#include "InterpreterWithOptions.h"

//#define DEBUG 1

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Error: Не были полученны файлы");
    }

	char **arrayOfCommands = initCommands();
	int sideOfResultVariable = LEFT;
	char sideOfOperation[5] = "OP()";

	if((setOptions(argv[1], arrayOfCommands, &sideOfResultVariable, sideOfOperation)) == 0)
    {
        printf("Error: Файла с настройками не существует\n");
        freeCommands(arrayOfCommands);
        exit(ERROR_OPTION_FILE_NOT_EXIST);
    }

	FILE* inputFileWithInstructions;
	if ((inputFileWithInstructions = fopen(argv[2], "r")) == NULL)
	{
	    printf("Error: Файла с инструкциями не существует\n");
        freeCommands(arrayOfCommands);
		exit(ERROR_FILE_WITH_INSTRUCTION_NOT_EXIST);
	}

	char buff[BUFSIZ],
	     leftExpression[BUFSIZ],
	     rightExpression[BUFSIZ],
	     *pstr;

	BinaryTree* treeOfVariables = NULL;
	int numberOfCommand,
	    errorNumber;

	while (!feof(inputFileWithInstructions))
	{
		*buff = '\0';

		if ((errorNumber = readInstructionFromFile(inputFileWithInstructions, buff)) != 0)
		{
            error(buff, errorNumber, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
		}

		if (strlen(buff) == 0)
		{
			continue;
		}

        findLeftAndRightExpr(buff, leftExpression, rightExpression, arrayOfCommands[9]);

		if(strstr(buff, arrayOfCommands[8]) != NULL)
        {
            if (strcmp(sideOfOperation, "OP()") == 0)
            {
                pstr = buff + strlen(arrayOfCommands[8]);

                if (*pstr++ == '(')
                {
                    if((errorNumber = printVariable(treeOfVariables, pstr, ");")) != 0)
                    {
                        error(buff, errorNumber, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
                    }

                    continue;
                }
                else
                {
                    error(buff, ERROR_UNKNOWN_COMMAND, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
                }
            }
            else
            {
                pstr = leftExpression;

                char *pstr2 = strchr(leftExpression, ')');

                if(pstr2 == NULL)
                {
                    error(buff, ERROR_CLOSING_BRACKET_NOT_FOUND, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
                }

                char *endOfInstruction = pstr + strlen(pstr) - 1;
                if(*endOfInstruction != ';')
                {
                    error(buff, ERROR_SEMICOLON_NOT_FOUND, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
                }

                if (*pstr++ == '(')
                {
                    *pstr2 = '\0';

                    if((errorNumber = printVariable(treeOfVariables, pstr, NULL)) != 0)
                    {
                        error(buff, errorNumber, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
                    }

                    continue;
                }
                else
                {
                    error(buff, ERROR_UNKNOWN_COMMAND, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
                }
            }
        }
        if (sideOfResultVariable == LEFT)
		{
            if(strstr(buff, arrayOfCommands[7]) != NULL && strstr(buff, "()") != NULL)
            {
                if (strcmp(sideOfOperation, "OP()") == 0)
                {
                    if ((treeOfVariables = readValue(treeOfVariables, leftExpression, sideOfResultVariable)) == NULL)
                    {
                        error(buff, ERROR_SEMICOLON_NOT_FOUND, inputFileWithInstructions, treeOfVariables,
                              arrayOfCommands);
                    }

                    continue;
                }
                else
                {
                    pstr = rightExpression;
                    char *end;
                    if((end = strchr(rightExpression, ';')) == NULL)
                    {
                        error(buff, ERROR_SEMICOLON_NOT_FOUND, inputFileWithInstructions, treeOfVariables,
                              arrayOfCommands);
                    }

                    *end = '\0';

                    treeOfVariables = readValue(treeOfVariables, leftExpression, sideOfResultVariable);

                    continue;
                }
            }

			if (strcmp(sideOfOperation, "OP()") == 0)
			{
                numberOfCommand = searchCommand(rightExpression, arrayOfCommands);

                pstr = rightExpression + strlen(arrayOfCommands[numberOfCommand]);
				if (numberOfCommand != COMMAND_NOT_FOUND && *pstr++ == '(')
				{
					if ((treeOfVariables = exeOperation(treeOfVariables, leftExpression, pstr, numberOfCommand,
                                                        sideOfResultVariable, sideOfOperation, &errorNumber)) != NULL)
                    {
					    error(buff, errorNumber, inputFileWithInstructions, treeOfVariables,
                              arrayOfCommands);
                    }
					continue;
				}
			}
			else
			{
				char *pstr2 = strchr(rightExpression, ')') + 1;

                numberOfCommand = searchCommand(pstr2, arrayOfCommands);

                pstr = pstr2 + strlen(*(arrayOfCommands + numberOfCommand));

				if(*pstr != ';')
                {
                    error(buff, ERROR_SEMICOLON_NOT_FOUND, inputFileWithInstructions, treeOfVariables,
                          arrayOfCommands);
                }

				if (numberOfCommand != COMMAND_NOT_FOUND)
				{
					*--pstr2 = '\0';

					pstr = rightExpression + 1;
                    if ((treeOfVariables = exeOperation(treeOfVariables, leftExpression, pstr, numberOfCommand,
                                                        sideOfResultVariable, sideOfOperation, &errorNumber)) == NULL)
                    {
                        error(buff, errorNumber, inputFileWithInstructions, treeOfVariables,
                              arrayOfCommands);
                    }

					continue;
				}
			}

            error(buff, ERROR_UNKNOWN_COMMAND, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
		}
		else
		{
			if(strstr(leftExpression,arrayOfCommands[7]) != NULL)
            {
                if (strcmp(sideOfOperation, "OP()") == 0)
                {
                    pstr = leftExpression + strlen(*(arrayOfCommands + 7));
                    if (*pstr++ == '(')
                    {
                        if(*pstr != ')')
                        {
                            error(buff, ERROR_CLOSING_BRACKET_NOT_FOUND, inputFileWithInstructions,
                                    treeOfVariables, arrayOfCommands);
                        }

                        if ((treeOfVariables = readValue(treeOfVariables, rightExpression, sideOfResultVariable)) == NULL)
                        {
                            error(buff, ERROR_SEMICOLON_NOT_FOUND, inputFileWithInstructions, treeOfVariables,
                                  arrayOfCommands);
                        }

                        continue;
                    }
                }
                else
                {
                    pstr = leftExpression;
                    if (*pstr++ == '(')
                    {
                        if (*pstr != ')')
                        {
                            error(buff, ERROR_CLOSING_BRACKET_NOT_FOUND, inputFileWithInstructions,
                                  treeOfVariables, arrayOfCommands);
                        }

                        if ((treeOfVariables = readValue(treeOfVariables, rightExpression, sideOfResultVariable)) == NULL)
                        {
                            error(buff, ERROR_SEMICOLON_NOT_FOUND, inputFileWithInstructions, treeOfVariables,
                                  arrayOfCommands);
                        }
                        continue;
                    }
                }
            }

			if (strcmp(sideOfOperation, "OP()") == 0)
			{
                numberOfCommand = searchCommand(leftExpression, arrayOfCommands);

                pstr = leftExpression + strlen(*(arrayOfCommands + numberOfCommand));
                if (numberOfCommand != COMMAND_NOT_FOUND && *pstr++ == '(')
				{
                    if ((treeOfVariables = exeOperation(treeOfVariables, rightExpression, pstr, numberOfCommand,
                                                       sideOfResultVariable, sideOfOperation, &errorNumber)) == NULL)
                    {
                        error(buff, errorNumber, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
                    }

                    continue;
				}
			}
			else
			{
				char *pstr2 = strchr(leftExpression, ')') + 1;
				if(pstr2 == NULL)
                {
				    error(buff, ERROR_CLOSING_BRACKET_NOT_FOUND, inputFileWithInstructions, treeOfVariables,
				            arrayOfCommands);
                }

                numberOfCommand = searchCommand(pstr2, arrayOfCommands);

                pstr = rightExpression + strlen(rightExpression) - 1;
				if (numberOfCommand != COMMAND_NOT_FOUND)
				{
				    if(*pstr != ';')
                    {
                        error(buff, ERROR_SEMICOLON_NOT_FOUND, inputFileWithInstructions, treeOfVariables,
                              arrayOfCommands);
                    }

					*pstr = '\0';
					*--pstr2 = '\0';

					if ((treeOfVariables = exeOperation(treeOfVariables, rightExpression, leftExpression + 1,
					        numberOfCommand,sideOfResultVariable, sideOfOperation, &errorNumber)) == NULL)
                    {
					    error(buff, errorNumber, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
                    }

					continue;
				}
			}

            error(buff, ERROR_UNKNOWN_COMMAND, inputFileWithInstructions, treeOfVariables, arrayOfCommands);
		}
	}

    freeTree(treeOfVariables);
    freeCommands(arrayOfCommands);

	return 0;
}