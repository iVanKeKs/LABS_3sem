//
// Created by iVan on 25.08.2020.
//

#ifndef INC_7_INTERPRETERWITHOPTIONS_H
#define INC_7_INTERPRETERWITHOPTIONS_H

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "Tree.h"

#define COMMANDS_COUNT 10

#define CALC_COUNT 7

#define LEFT 0
#define RIGHT 1

#define COMMAND_NOT_FOUND -1

char **initCommands();
int setOptions(char *nameOfFile, char **arrayOfCommands, int *sideOfResultVariable, char *sideOfOperation);
void freeCommands(char **commands);

int readInstructionFromFile(FILE *fleInput, char *line);
int searchCommand(char *inputString, char **arrayOfCommands);

BinaryTree* readValue(BinaryTree *headTree, char *nameOfVariable, int sideOfResultVariable);
int printVariable(BinaryTree *headTree, char *line, char *endOfInstruction);

void findLeftAndRightExpr(char *inputString, char *leftExpression, char *rightExpression, char *assignmentOperation);

BinaryTree* exeOperation(BinaryTree *headTree, char *leftExpression, char *rightExpression, int numberOfOperation,
                         int sideOfResultVariable, char *sideOfOperation, int *errorNumber);

#define ERROR_OPTION_FILE_NOT_EXIST -1
#define ERROR_FILE_WITH_INSTRUCTION_NOT_EXIST ERROR_OPTION_FILE_NOT_EXIST - 1

#define ERROR_INVALID_COMMENT 1
#define ERROR_BUFF_IS_SHORT ERROR_INVALID_COMMENT + 1
#define ERROR_SEMICOLON_NOT_FOUND ERROR_BUFF_IS_SHORT + 1
#define ERROR_VAR_NOT_EXIST ERROR_SEMICOLON_NOT_FOUND + 1
#define ERROR_CLOSING_BRACKET_NOT_FOUND ERROR_VAR_NOT_EXIST + 1
#define ERROR_UNKNOWN_COMMAND ERROR_CLOSING_BRACKET_NOT_FOUND + 1
#define ERROR_SECOND_VAR_NOT_FOUND ERROR_UNKNOWN_COMMAND + 1
#define ERROR_DIVISION_BY_ZERO ERROR_SECOND_VAR_NOT_FOUND + 1

void error(char *instruction, int numberOfError, FILE *inputFile, BinaryTree *headTree, char **arrayOfCommands);


#endif //INC_7_INTERPRETERWITHOPTIONS_H
