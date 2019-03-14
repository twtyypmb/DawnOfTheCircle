#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Monster.h"
#include "DebugTools.h"


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
    int i,j,k,index;
    PrintDebugLine(StringConcat(buffer,MONSTER_FILE_PATH,itoa(monster_number,word,10),MONSTER_EXTENSION));
    FILE* fp = fopen(buffer,"r");
    do
    {
        if(NULL == fp)
        {
            break;
        }
        temp->_game_object_ptr = NewGameObject(NULL);
        FGetsNoReturn(temp->_game_object_ptr->Name,200,fp);
        fgets(buffer,200,fp);

        index = 0;
        // 读取事件编号
        if(true)
        {
            sscanf(buffer+index,"%s",word);
            //PrintDebugLine(word);
            index += strlen(word);
            temp->event_number = atoi(word);
        }


        for(k=0;k<GAME_OBJECT_FRAME_MAX;k++)
        {
            sscanf(buffer+index,"%s",word);
            index += strlen(word);
            //PrintDebugLine(word);
            temp->_game_object_ptr->Frames[0][0][k] = GetTransparentTexture(atoi(word));
        }
        // 读取每一帧
        for(i=1;i<STATUS_ENUM_MAX;i++)
        {
            for(j=1;j<DIRECTION_ENUM_MAX;j++)
            {
                for(k=0;k<GAME_OBJECT_FRAME_MAX;k++)
                {
                    temp->_game_object_ptr->Frames[i][j][k] = temp->_game_object_ptr->Frames[0][0][k];
                }

            }
        }
        //temp-> = LoadImage(StringConcat(buffer,MONSTER_FILE_PATH,itoa(monster_number,word,10),MONSTER_EXTENSION));

        fclose(fp);
        return temp;
    }while(false);

    fclose(fp);
    FreeMonster(temp);
    return NULL;
}

void FreeMonster(PMonster monster_ptr)
{
    FreeGameObject(monster_ptr->_game_object_ptr);
    //SDL_DestroyTexture(monster_ptr->_texture);
    free(monster_ptr);
}
