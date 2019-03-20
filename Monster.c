#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Monster.h"
#include "DebugTools.h"
#include "GameCoreProcessInterface.h"


const char* MONSTER_FILE_PATH = "resource/monster/";
const char* MONSTER_EXTENSION = ".mst";

static PPosition GetPositionCore(void * _this_obj)
{
    PMonster _this=(PMonster)_this_obj;
    return _this->living_thing_ptr->game_object_ptr->GetPosition(_this->living_thing_ptr->game_object_ptr);
}

static void HandleEventCore(void* obj)
{
    PMonster _this = (PMonster)obj;
    GameCoreProcessInterface_HandleEvent(_this->living_thing_ptr);
}

static void UpdateDataCore(void* obj)
{
    PMonster _this = (PMonster)obj;
    GameCoreProcessInterface_UpdateData(_this->living_thing_ptr);
}
static void RenderCore(void* obj)
{
    PMonster _this = (PMonster)obj;
    GameCoreProcessInterface_Render(_this->living_thing_ptr);
}

SDL_Texture* GetMonsterTexture( int number )
{
   return GetTransparentTexture(GetTotalSurface(),number,GetTotalBackSurface(),number);
}

PMonster NewMonster(int monster_number )
{
    PMonster temp = (PMonster)malloc(sizeof(Monster));
    temp->GetPosition = GetPositionCore;
    temp->HandleEvent = HandleEventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    char buffer[200];
    char word[10];
    char c = ' ';
    int i,j,k,index;
    DebugTools_PrintDebugLine(Utils_StringConcat(buffer,MONSTER_FILE_PATH,itoa(monster_number,word,10),MONSTER_EXTENSION));
    FILE* fp = fopen(buffer,"r");
    do
    {
        if(NULL == fp)
        {
            break;
        }
        temp->living_thing_ptr = NewLivingThing();
        Utils_FGetsNoReturn(temp->living_thing_ptr->game_object_ptr->Name,200,fp);
        fgets(buffer,200,fp);

        index = 0;
        // 读取事件编号
        if(true)
        {
            sscanf(buffer+index,"%s",word);
            //DebugTools_PrintDebugLine(word);
            index += strlen(word);
            temp->event_number = atoi(word);
        }


        for(k=0;k<LIVING_THING_FRAME_MAX;k++)
        {
            sscanf(buffer+index,"%s",word);
            index += strlen(word);
            //DebugTools_PrintDebugLine(word);
            temp->living_thing_ptr->Frames[0][0][k] = GetMonsterTexture(atoi(word));
        }
        // 读取每一帧
        for(i=1;i<STATUS_ENUM_MAX;i++)
        {
            for(j=1;j<DIRECTION_ENUM_MAX;j++)
            {
                for(k=0;k<LIVING_THING_FRAME_MAX;k++)
                {
                    temp->living_thing_ptr->Frames[i][j][k] = temp->living_thing_ptr->Frames[0][0][k];
                }

            }
        }
        //temp-> = LoadImage(Utils_StringConcat(buffer,MONSTER_FILE_PATH,itoa(monster_number,word,10),MONSTER_EXTENSION));

        fclose(fp);
        return temp;
    }while(false);

    fclose(fp);
    FreeMonster(temp);
    return NULL;
}

void FreeMonster(PMonster monster_ptr)
{
    FreeGameObject(monster_ptr->living_thing_ptr->game_object_ptr);
    //SDL_DestroyTexture(monster_ptr->_texture);
    free(monster_ptr);
}


