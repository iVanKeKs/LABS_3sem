//
// Created by iVan on 25.08.2020.
//

#include "InterpreterWithOptions.h"

void setCommand(char** arrayOfCommands, int numberOfCommand, char* newCommand)
{
    arrayOfCommands[numberOfCommand] = (char*)realloc(arrayOfCommands[numberOfCommand], sizeof(char) * strlen(newCommand) + 1);
    strcpy(arrayOfCommands[numberOfCommand], newCommand);
}

char **initCommands()
{
    char **commands = (char**)malloc(sizeof(char*) * COMMANDS_COUNT);
    setCommand(commands, 0, "ADD");
    setCommand(commands, 1, "MULT");
    setCommand(commands, 2, "SUB");
    setCommand(commands, 3, "POW");
    setCommand(commands, 4, "DIV");
    setCommand(commands, 5, "REM");
    setCommand(commands, 6, "XOR");
    setCommand(commands, 7, "INPUT");
    setCommand(commands, 8, "OUTPUT");
    setCommand(commands, 9, "=");

    return commands;
}

int setOptions(char* nameOfFile, char **arrayOfCommands, int *sideOfResultVariable, char *sideOfOperation)
{
    FILE* fileWithOptions;
    if ((fileWithOptions = fopen(nameOfFile, "r")) == NULL)
    {
        printf("Error: Файла с настройками не сущесвтует\n");
        return 0;
    }

    char buff[BUFSIZ],
         *pbuff;

    while (!feof(fileWithOptions))
    {
        *buff = '\0';
        pbuff = buff;
        fgets(buff, BUFSIZ, fileWithOptions);

        while(*pbuff != '\0' && *pbuff != '\r' && *pbuff != '\n')
        {
            if(*pbuff == '#')
            {
                *pbuff = '\0';
                break;
            }
            *pbuff++ = toupper(*pbuff);
        }

        *pbuff = '\0';

        if(strcmp(buff, "LEFT=") == 0)
        {
            *sideOfResultVariable = LEFT;
        }
        else if(strcmp(buff, "RIGHT=") == 0)
        {
            *sideOfResultVariable = RIGHT;
        }
        else if(strcmp(buff, "OP()") == 0)
        {
            strcpy(sideOfOperation, "OP()");
        }
        else if(strcmp(buff, "()OP") == 0)
        {
            strcpy(sideOfOperation, "()OP");
        }
        else
        {
            pbuff = strchr(buff, ' ');
            *pbuff++ = '\0';

            if(strcmp(buff, "ADD") == 0)
            {
                setCommand(arrayOfCommands, 0, pbuff);
            }
            else if(strcmp(buff, "MULT") == 0)
            {
                setCommand(arrayOfCommands, 1, pbuff);
            }
            else if(strcmp(buff, "SUB") == 0)
            {
                setCommand(arrayOfCommands, 2, pbuff);
            }
            else if(strcmp(buff, "POW") == 0)
            {
                setCommand(arrayOfCommands, 3, pbuff);
            }
            else if(strcmp(buff, "DIV") == 0)
            {
                setCommand(arrayOfCommands, 4, pbuff);
            }
            else if(strcmp(buff, "REM") == 0)
            {
                setCommand(arrayOfCommands, 5, pbuff);
            }
            else if(strcmp(buff, "XOR") == 0)
            {
                setCommand(arrayOfCommands, 6, pbuff);
            }
            else if(strcmp(buff, "INPUT") == 0)
            {
                setCommand(arrayOfCommands, 7, pbuff);
            }
            else if(strcmp(buff, "OUTPUT") == 0)
            {
                setCommand(arrayOfCommands, 8, pbuff);
            }
            else if(strcmp(buff, "=") == 0)
            {
                setCommand(arrayOfCommands, 9, pbuff);
            }
            else
            {
                printf("Non fatal error: Неизвестная команда %s %s\n", buff, pbuff);
            }
        }
    }

    return 1;
}

void freeCommands(char **commands)
{
    for (int i = 0; i < COMMANDS_COUNT; i++)
    {
        free(commands[i]);
    }

    free(commands);
}

int readInstructionFromFile(FILE *fleInput, char *line)
{
    char buffChar;
    int flag = 0;

    while (!feof(fleInput))
    {
        buffChar = toupper(fgetc(fleInput));

        if (flag == 0)
        {
            if (isspace(buffChar) || buffChar == EOF)
            {
                continue;
            }

            if (buffChar == ';')
            {
                *line++ = buffChar;
                *line = '\0';
                return 0;
            }
            else if (buffChar == '#')
            {
                flag = -1;
            }
            else if (buffChar == '[')
            {
                flag++;
            }
            else if (buffChar == ']')
            {
                *line = '\0';
                return 1;
            }
            else
            {
                *line++ = buffChar;
            }
        }
        else if (flag == -1)
        {
            if (buffChar == '\n')
            {
                flag = 0;
            }
        }
        else if (flag > 0)
        {
            if (buffChar == ']')
            {
                flag--;
            }
            else if (buffChar == '[')
            {
                flag++;
            }
        }
    }

    if (flag != 0)
    {
        return 1;
    }
    else
    {
        *line = '\0';
        return 0;
    }
}

int searchCommand(char* inputString, char **arrayOfCommands)
{
    for (int numberOfCommand = 0; numberOfCommand < CALC_COUNT; ++numberOfCommand)
    {
        if(strstr(inputString, arrayOfCommands[numberOfCommand]) != NULL)
        {
            return numberOfCommand;
        }
    }

    return COMMAND_NOT_FOUND;
}

void findLeftAndRightExpr(char *inputString, char *leftExpression, char *rightExpression, char *assignmentOperation)
{
    *leftExpression = '\0';
    *rightExpression = '\0';

    int i = 0;

    char *pbuff = strstr(inputString, assignmentOperation);

    for (; i < strlen(inputString) + 1; ++i)
    {
        if(pbuff == inputString + i)
        {
            *(leftExpression + i) = '\0';
            break;
        }

        leftExpression[i] = inputString[i];
    }

    i += strlen(assignmentOperation);

    strcpy(rightExpression, inputString + i);
}

int xorCalculation(int leftValue, int rightValue)
{
    int resultValue = 0,
        i = 1;

    while (leftValue || rightValue)
    {
        if ((!(leftValue & 1) && (rightValue & 1)) || ((leftValue & 1) && !(rightValue & 1)))
        {
            resultValue += i;
            i *= 2;
        }
        else
        {
            i *= 2;
        }

        leftValue = leftValue >> 1;
        rightValue = rightValue >> 1;
    }

    return resultValue;
}

BinaryTree* readValue(BinaryTree* headTree, char* nameOfVariable, int sideOfResultVariable)
{
    if (sideOfResultVariable == RIGHT)
    {
        char *endOfInstruction = strchr(nameOfVariable, ';');
        if (endOfInstruction != NULL)
        {
            *endOfInstruction = '\0';
        }
        else
        {
            return NULL;
        }
    }

    int newValue = 0;
    printf("Введите %s: ", nameOfVariable);
    scanf("%d", &newValue);

    return insertExistNode(headTree, createNewNode(nameOfVariable, newValue));
}

int printVariable(BinaryTree *headTree, char *line, char *endOfInstruction)
{
    if (strlen(line) < 1)
    {
        return ERROR_BUFF_IS_SHORT;
    }

    if (endOfInstruction != 0)
    {
        char *positionOfEndLiter = strstr(line, endOfInstruction);
        if(positionOfEndLiter != NULL)
        {
            *positionOfEndLiter = '\0';
        }
        else
        {
            return ERROR_SEMICOLON_NOT_FOUND;
        }
    }

    BinaryTree* find = searchByNameOfVar(headTree, line);

    if (find != NULL)
    {
        printNode(find, 0);
    }
    else
    {
        return ERROR_VAR_NOT_EXIST;
    }

    return 0;
}

int calculate(int leftValue, int rightValue, int numberOfOperation, int *error)
{
    switch(numberOfOperation)
    {
        case(0):
        {
            return leftValue + rightValue;
        }
        case(1):
        {
            return leftValue * rightValue;
        }
        case(2):
        {
            return leftValue - rightValue;
        }
        case(3):
        {
            int temp = leftValue;
            for (int i = rightValue; i > 1; i--)
            {
                leftValue *= temp;
            }
            return leftValue;
        }
        case(4):
        {
            if (rightValue == 0)
            {
                *error = 1;
                return 0;
            }
            return leftValue / rightValue;
        }
        case(5):
        {
            return leftValue % rightValue;
        }
        case(6):
        {
            return xorCalculation(leftValue, rightValue);
        }
    }
}

BinaryTree* exeOperation(BinaryTree* headTree, char* leftExpression, char* rightExpression, int numberOfOperation,
                         int sideOfResultVariable, char *sideOfOperation, int *errorNumber)
{
    if (sideOfResultVariable == LEFT)
    {
        if (strcmp(sideOfOperation, "OP()") == 0)
        {
            if (*(rightExpression + strlen(rightExpression) - 1) == ';')
            {
                *(rightExpression + strlen(rightExpression) - 1) = '\0';
            }
            else
            {
                *errorNumber = ERROR_SEMICOLON_NOT_FOUND;
                return NULL;
            }

            if (*(rightExpression + strlen(rightExpression) - 1) == ')')
            {
                *(rightExpression + strlen(rightExpression) - 1) = '\0';
            }
            else
            {
                *errorNumber = ERROR_CLOSING_BRACKET_NOT_FOUND;
                return NULL;
            }
        }
    }
    else
    {
        if (!strcmp(sideOfOperation, "OP()"))
        {
            if (*(rightExpression + strlen(rightExpression) - 1) == ')')
            {
                *(rightExpression + strlen(rightExpression) - 1) = '\0';
            }
            else
            {
                *errorNumber = ERROR_CLOSING_BRACKET_NOT_FOUND;
                return NULL;
            }

            if (*(leftExpression + strlen(leftExpression) - 1) == ';')
            {
                *(leftExpression + strlen(leftExpression) - 1) = '\0';
            }
            else
            {
                *errorNumber = ERROR_SEMICOLON_NOT_FOUND;
                return NULL;
            }
        }
    }

    char *secondVariable = NULL;

    for (int i = 0; i < strlen(rightExpression); ++i)
    {
        if (rightExpression[i] == ',')
        {
            *(rightExpression + i) = 0;
            secondVariable = rightExpression + i + 1;
        }
    }

    if (secondVariable == NULL)
    {
        *errorNumber = ERROR_SECOND_VAR_NOT_FOUND;
        return NULL;
    }

    BinaryTree* resultVariable = searchByNameOfVar(headTree, leftExpression);
    BinaryTree* leftVariable = searchByNameOfVar(headTree, rightExpression);
    BinaryTree* rightVariable = searchByNameOfVar(headTree, secondVariable);

    if (leftVariable == NULL || rightVariable == NULL)
    {
        *errorNumber = ERROR_VAR_NOT_EXIST;
        return NULL;
    }

    int divisionByZero = 0;

    if (resultVariable != NULL)
    {
        resultVariable->data = calculate(leftVariable->data, rightVariable->data, numberOfOperation, &divisionByZero);
        if(divisionByZero == 1)
        {
            *errorNumber = ERROR_DIVISION_BY_ZERO;
            return NULL;
        }
        return headTree;
    }
    else
    {
        BinaryTree *buff = insertExistNode(headTree, createNewNode(leftExpression, calculate(leftVariable->data,
                                           rightVariable->data, numberOfOperation, &divisionByZero)));

        if(divisionByZero == 1)
        {
            *errorNumber = ERROR_DIVISION_BY_ZERO;
            return NULL;
        }

        return buff;
    }
}

char *errors[] = {"Не закрыт комментарий",
                  "Строка силшком короткая",
                  "Точка с запятой не обнаружена",
                  "Одной из переменной не существует",
                  "Закрывающая скобка не найдена",
                  "Неизсветсная команда",
                  "Вторая переменная не введена",
                  "Деление на ноль"};

void error(char* instruction, int numberOfError, FILE* inputFile, BinaryTree* headTree, char** arrayOfCommands)
{
    printf("Строка - \"%s\"\nError: %s\n", instruction, errors[numberOfError - 1]);
    fclose(inputFile);
    freeTree(headTree);
    freeCommands(arrayOfCommands);
    exit(numberOfError);
}