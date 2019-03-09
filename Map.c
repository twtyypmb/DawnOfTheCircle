#include "Map.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"


const char* MAP_PATH = "resource\\floor\\";
const char* MAP_EXTENSION = ".floor";

static bool InitCore(PMap _this,int map_number)
{
    char buffer[1024];
    char number[10];
    char c = ' ';
    FILE* file_ptr = fopen(strcpy(strcpy(strcpy(buffer,MAP_PATH),itoa(map_number,number,10)),MAP_EXTENSION),"r");
    if(file_ptr!=NULL)
    {
        // ¶ÁÈ¡µØÍ¼Ãû³Æ
        while( strlen((fgets(buffer,1024,file_ptr))));
        strcpy(_this->MapName,buffer);

        _this->UpInitialPositionPtr = NewPosition();
        //
        while( (c = fgetc(file_ptr)) == ' ');
        _this->UpInitialPositionPtr->X = (int)(c-'0');

        while( (c = fgetc(file_ptr)) == ' ');
        _this->UpInitialPositionPtr->Y = (int)(c-'0');

        while( (c = fgetc(file_ptr)) == ' ');
        _this->DownInitialPositionPtr->X = (int)(c-'0');

        while( (c = fgetc(file_ptr)) == ' ');
        _this->DownInitialPositionPtr->Y= (int)(c-'0');

        while( (c = fgetc(file_ptr)) == ' ');
        _this->BGMPtr = NewBGM( (int)(c-'0') );



    }
    return true;
}

static void HandleEnventCore(void* _this)
{


}

static void UpdateDataCore(void* _this)
{
    PMap this = (PMap)_this;
}

static void RenderCore(void* _this)
{
    PMap this = (PMap)_this;

}


PMap NewMap( void )
{
    PMap map_ptr = (PMap)malloc(sizeof(Map));
    map_ptr->Init=InitCore;
    map_ptr->UpInitialPositionPtr=NULL;
    map_ptr->DownInitialPositionPtr=NULL;
    map_ptr->HandleEnvent = HandleEnventCore;
    map_ptr->UpdateData = UpdateDataCore;
    map_ptr->Render = RenderCore;
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
