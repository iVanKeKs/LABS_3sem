//
// Created by iVan on 11.08.2020.
//

#ifndef INC_1_TECHNICALMETODS_H
#define INC_1_TECHNICALMETODS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR_COMMAND_LINE_PARAMETERS 1
#define ERROR_FILE_NOT_EXIST ERROR_COMMAND_LINE_PARAMETERS + 1
#define ERROR_ARRAY_NOT_EXIST ERROR_FILE_NOT_EXIST + 1
#define ERROR_ARRAY_IS_SHORT ERROR_ARRAY_NOT_EXIST + 1
#define ERROR_INVALID_INDEX ERROR_ARRAY_NOT_EXIST + 1
#define ERROR_INVALID_COMMAND ERROR_INVALID_INDEX + 1

void error(int errorNumber);

int sortFromLargestToSmallest(const int *leftElement, const int *rightElement);
int sortFromSmallestToLargest(const int *leftElement, const int *rightElement);

#endif //INC_1_TECHNICALMETODS_H