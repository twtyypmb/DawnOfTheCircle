#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

char * FGetSNoReturn(char *,int, FILE*);
void FileGoToNextLine(FILE*);
char* StringConcat(char* buffer, const char* first_string,const char* second_string,const char* third_string);

#endif // UTILS_H
