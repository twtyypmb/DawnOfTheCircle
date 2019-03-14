#include "Utils.h"
#include "string.h"

char * FGetsNoReturn(char *buffer,int max, FILE* fp)
{
    fgets(buffer,max,fp);
    buffer[strlen(buffer)-1] = '\0';
    return buffer;
}


void FileGoToNextLine(FILE* fp)
{
    char buffer[4096];
    fgets(buffer,4096,fp);
}

char* StringConcat(char* buffer, const char* first_string,const char* second_string,const char* third_string)
{
    char * map_file_temp = strcpy(buffer,first_string);
    //PrintDebugInfo("%s\n",buffer);
    map_file_temp = buffer+strlen(buffer);
    strcpy(map_file_temp,second_string );
    //PrintDebugInfo("%s\n",buffer);
    map_file_temp = buffer+strlen(buffer);
    strcpy(map_file_temp,third_string);
    //PrintDebugInfo("%s\n",buffer);

    return buffer;
}
