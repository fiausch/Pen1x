#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

int strlen(const char* ptr);
int strnlen(const char* ptr, int max);
int tonumericdigit(char c);
bool isdigit(char c);
char* strcpy(char *, const char *);
int strncmp(const char* str1, const char* str2, int n);
char tolower(char s1);
int istrncmp(const char* str1, const char* str2, int n);


#endif