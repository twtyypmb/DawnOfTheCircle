#include "Utils.h"
#include "string.h"

char * Utils_FGetsNoReturn(char *buffer,int max, FILE* fp)
{
    fgets(buffer,max,fp);
    buffer[strlen(buffer)-1] = '\0';
    return buffer;
}


void Utils_FileGoToNextLine(FILE* fp)
{
    char buffer[4096];
    fgets(buffer,4096,fp);
}

char* Utils_StringConcat(char* buffer, const char* first_string,const char* second_string,const char* third_string)
{
    char * map_file_temp = strcpy(buffer,first_string);
    //DebugTools_PrintDebugInfo("%s\n",buffer);
    map_file_temp = buffer+strlen(buffer);
    strcpy(map_file_temp,second_string );
    //DebugTools_PrintDebugInfo("%s\n",buffer);
    map_file_temp = buffer+strlen(buffer);
    strcpy(map_file_temp,third_string);
    //DebugTools_PrintDebugInfo("%s\n",buffer);

    return buffer;
}
