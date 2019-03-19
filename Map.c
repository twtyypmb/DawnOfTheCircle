#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "Utils.h"
#include "Map.h"


const char* MAP_PATH = "resource\\floor\\";
const char* MAP_EXTENSION = ".floor";




static int GetMapRowCore(PMap _this)
{
    return _this->_map_row;
}

static int GetMapColCore(PMap _this)
{
    return _this->_map_col;
}

static void HandleEnventCore(void* _this)
{


}

static void UpdateDataCore(void* _this)
{
    PMap this = (PMap)_this;
}

static void RenderCore(void* _this_obj)
{
    PMap _this = (PMap)_this_obj;
    int i,j;
    for(i = 0;i<MAP_MAX_ROW;i++)
    {
        for(j = 0;j<MAP_MAX_COL;j++)
        {
            if(NULL != _this->_monsters_ptr[i][j])
            {
                _this->_monsters_ptr[i][j]->Render(_this->_monsters_ptr[i][j]);
            }

        }
    }
}


PMap NewMap( int map_number )
{
    PMap map_ptr = (PMap)malloc(sizeof(Map));

    map_ptr->GetMapCol = GetMapColCore;
    map_ptr->GetMapRow=GetMapRowCore;
    map_ptr->UpInitialPositionPtr=NULL;
    map_ptr->DownInitialPositionPtr=NULL;
    map_ptr->HandleEnvent = HandleEnventCore;
    map_ptr->UpdateData = UpdateDataCore;
    map_ptr->Render = RenderCore;


    char buffer[1024];
    char number[10];
    char c = ' ';
    int i = 0,j=0;
    map_ptr->_map_col=map_ptr->_map_row=0;
    Utils_StringConcat(buffer,MAP_PATH,itoa(map_number,number,10),MAP_EXTENSION);

    FILE* file_ptr = fopen(buffer,"r");
    if(file_ptr!=NULL)
    {
        //
        Utils_FGetsNoReturn(buffer,1024,file_ptr);
        strcpy(map_ptr->MapName,buffer);
        DebugTools_PrintDebugInfo("%s\n", map_ptr->MapName);

        map_ptr->UpInitialPositionPtr = NewPosition();
        //
        while( (c = fgetc(file_ptr)) == ' ');
        map_ptr->UpInitialPositionPtr->X = (int)(c-'0');

        while( (c = fgetc(file_ptr)) == ' ');
        map_ptr->UpInitialPositionPtr->Y = (int)(c-'0');

        map_ptr->DownInitialPositionPtr = NewPosition();
        while( (c = fgetc(file_ptr)) == ' ');
        map_ptr->DownInitialPositionPtr->X = (int)(c-'0');

        while( (c = fgetc(file_ptr)) == ' ');
        map_ptr->DownInitialPositionPtr->Y= (int)(c-'0');

        while( (c = fgetc(file_ptr)) == ' ');
        map_ptr->BGMPtr = NewBGM( (int)(c-'0') );


        // 跳过当前行
        Utils_FileGoToNextLine(file_ptr);

        char buffer[100];
        char word[10];
        int index = 0;
        i=0;
        while(fgets(buffer,100,file_ptr)!=NULL)
        {

            //DebugTools_PrintDebugInfo("buffer:%s,buffer.length=%d\n",buffer,strlen(buffer));
            while( (i=sscanf(buffer+index,"%s",word)) > 0 )
            {
                DebugTools_PrintDebugInfo("word:%s,word.length=%d\n",word,strlen(word));
                index+=strlen(word);
                map_ptr->_monsters_ptr[map_ptr->_map_row][map_ptr->_map_col] = NewMonster(atoi(word));
                map_ptr->_map_col++;
            }
            map_ptr->_map_row++;
        }

    }

    return map_ptr;
}
void FreeMap( PMap map_ptr )
{
    if( map_ptr->UpInitialPositionPtr!=NULL )
    {
        FreePosition(map_ptr->UpInitialPositionPtr);
        map_ptr->UpInitialPositionPtr=NULL;
    }

    if( map_ptr->DownInitialPositionPtr!=NULL )
    {
        FreePosition(map_ptr->DownInitialPositionPtr);
        map_ptr->DownInitialPositionPtr=NULL;
    }

    free(map_ptr);
}
