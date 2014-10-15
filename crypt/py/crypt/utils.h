#include <stdlib.h>
#include <stdio.h>

#include "errors.h"

size_t fileSize(FILE *file);
void printArray(unsigned char *array, int array_length);
void exitWithError(int e, void *details);
