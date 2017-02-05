#include<stdio.h>
#include<string.h>
#include<ctype.h>

#ifndef MYSTRINGFUNCS_H
#define MYSTRINGFUNCS_H

/*
    Converts source to uppercase and stores it myString
*/
char* stringToUpper(char* myString, const char* source);

char* stringToLower(char* myString, const char* source);

int compareIgnoreCase(const char* s1, const char* s2);

#endif
