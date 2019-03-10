#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Monster.h"

const char* MONSTER_FILE_PATH = "resource/monster/";
const char* MONSTER_EXTENSION = ".mst";

static PPosition GetPositionCore(void * _this)
{
    PMonster this=(PMonster)_this;
    return this->_game_object_ptr->GetPosition(this->_game_object_ptr);
}

static void HandleEnventCore(void* obj)
{
    PMonster _this = (PMonster)obj;
    _this->HandleEnvent(_this->_game_object_ptr);
}

static void UpdateDataCore(void* obj)
{
    PMonster _this = (PMonster)obj;
    _this->UpdateData(_this->_game_object_ptr);
}
static void RenderCore(void* obj)
{
    PMonster _this = (PMonster)obj;
    _this->Render(_this->_game_object_ptr);
}


PMonster NewMonster(int monster_number )
{
    PMonster temp = (PMonster)malloc(sizeof(Monster));
    temp->GetPosition = GetPositionCore;
    temp->HandleEnvent = HandleEnventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    char buffer[200];
    char word[10];
    char c = ' ';
    FILE* fp = fopen(StringConcat(buffer,MONSTER_FILE_PATH,itoa(monster_number,word,10),MONSTER_EXTENSION),"r");
    do
    {
        if(NULL == fp)
        {
            break;
        }
        FGetSNoReturn(temp->_game_object_ptr->Name,200,fp);
        while( (c = fgetc(fp)) == ' ');temp->event_number = (int)(c-'0');
        while( (c = fgetc(fp)) == ' ');

        //toto:¶¨Òå×´Ì¬ºÍèåÍ¼Ïñ
        temp->_game_object_ptr->Frames[IDLE] =
        temp-> = LoadImage(StringConcat(buffer,MONSTER_FILE_PATH,itoa(monster_number,word,10),MONSTER_EXTENSION));
        temp->_game_object_ptr = NewGameObject(temp->_texture,NULL);

        return temp;
    }while(false);

    FreeMonster(temp);
    return NULL;
}

void FreeMonster(PMonster monster_ptr)
{
    FreeGameObject(monster_ptr->_game_object_ptr);
    SDL_DestroyTexture(monster_ptr->_texture);
    free(monster_ptr);
}
