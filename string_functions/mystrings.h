#include "stdio.h"
#include <ctype.h>
#include <string.h>

#ifndef MYSTRINGS_H
#define MYSTRINGS_H

char* stringToUpper(char* myString, const char* source);

char* stringToLower(char* myString, const char* source);

int compareIgnoreCase(const char* s1, const char* s2);

#endif
