#include <stdio.h>
#include <stdlib.h>
#include "Role.h"
#include "CommonResource.h"


static void HandleEventCore(void* obj)
{
    PRole _this = (PRole)obj;

    GameCoreProcessInterface_HandleEvent(_this->living_thing_ptr);
}


static void UpdateDataCore(void* _this_obj)
{
    PRole _this=(PRole)_this_obj;
    GameCoreProcessInterface_UpdateData(_this->living_thing_ptr);
}


static void RenderCore(void* _this_obj)
{
    PRole _this=(PRole)_this_obj;
    GameCoreProcessInterface_Render(_this->living_thing_ptr);
}

PRole NewRole(void)
{
    PRole temp=(PRole)malloc(sizeof(Role));
    temp->living_thing_ptr=NewLivingThing(GetSDLEvnet);
    temp->HandleEvent = HandleEventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    temp->living_thing_ptr->game_object_ptr->_position_ptr->X=10;
    temp->living_thing_ptr->game_object_ptr->_position_ptr->Y=10;
    int i,j,k,index,t,t_back;
    i=j=k=index=t=t_back=0;
    char buffer[200],word[10],frame1[10],frame2[10],frame3[10],frame4[10],frame5[10],frame6[10],frame7[10],frame8[10];
    FILE* fp = fopen("resource/role/img.rol","r");
    do
    {
        while( NULL != fgets(buffer,200,fp) && j<DIRECTION_ENUM_MAX  )
        {
            index =0;
            k=0;

            if(sscanf(buffer,"%s %s %s %s %s %s %s %s",frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8) < 1)
            {
                continue;
            }

            DebugTools_PrintDebugInfo("%s %s %s %s %s %s %s %s",frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8);
            temp->living_thing_ptr->Frames[IDLE][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame2),GetTotalSurface(),atoi(frame1));
            temp->living_thing_ptr->Frames[IDLE][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame4),GetTotalSurface(),atoi(frame3));
            temp->living_thing_ptr->Frames[IDLE][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame6),GetTotalSurface(),atoi(frame5));
            temp->living_thing_ptr->Frames[IDLE][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame8),GetTotalSurface(),atoi(frame7));
            DisPlayTexture(GetRenderer(),temp->living_thing_ptr->Frames[0][j][k-1]);

            j++;
        }

        j=0;
        while( NULL != fgets(buffer,200,fp) && j<DIRECTION_ENUM_MAX  )
        {
            index =0;
            k=0;

            if(sscanf(buffer,"%s %s %s %s %s %s %s %s",frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8) < 1)
            {
                continue;
            }

            DebugTools_PrintDebugInfo("%s %s %s %s %s %s %s %s",frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8);
            temp->living_thing_ptr->Frames[MOVING][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame2),GetTotalSurface(),atoi(frame1));
            temp->living_thing_ptr->Frames[MOVING][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame4),GetTotalSurface(),atoi(frame3));
            temp->living_thing_ptr->Frames[MOVING][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame6),GetTotalSurface(),atoi(frame5));
            temp->living_thing_ptr->Frames[MOVING][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame8),GetTotalSurface(),atoi(frame7));
            DisPlayTexture(GetRenderer(),temp->living_thing_ptr->Frames[MOVING][j][k-1]);

            j++;
        }

        fclose(fp);


        temp->living_thing_ptr->game_object_ptr->SwitchFrames(temp->living_thing_ptr->game_object_ptr,temp->living_thing_ptr->Frames[IDLE][UP],LIVING_THING_FRAME_MAX);

        return temp;
    }while(false);

    fclose(fp);
    FreeRole(temp);
    return temp;
}


void FreeRole(PRole role)
{
    FreeGameObject(role);
}
