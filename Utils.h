#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

char * Utils_FGetsNoReturn(char *,int, FILE*);
void Utils_FileGoToNextLine(FILE*);
char* Utils_StringConcat(char* buffer, const char* first_string,const char* second_string,const char* third_string);

#endif // UTILS_H
