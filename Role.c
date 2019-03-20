#include <stdio.h>
#include <stdlib.h>
#include "Role.h"
#include "CommonResource.h"


static void HandleEventCore(void* obj)
{
    PRole _this = (PRole)obj;
    GameObjectDirectionEnum d;
    SDL_Event temp_event;
    switch(temp_event.type)
    {
    case SDL_KEYDOWN:
        switch (temp_event.key.keysym.sym)
        {
        case SDLK_w:
            _this->living_thing_ptr->Velocity->Y = -1;
            d = UP;
            break;
        case SDLK_a:
            _this->living_thing_ptr->Velocity->X = -1;
            d = LEFT;
            break;
        case SDLK_d:
            _this->living_thing_ptr->Velocity->X = 1;
            d = RIGTH;
            break;
        case SDLK_s:
            _this->living_thing_ptr->Velocity->Y = 1;
            d = DOWN;
            break;
        default:
            break;
        }
        if( _this->living_thing_ptr->Status != MOVING )
        {
            _this->living_thing_ptr->game_object_ptr->SwitchFrames(_this->living_thing_ptr->game_object_ptr,_this->living_thing_ptr->Frames[MOVING][d],LIVING_THING_FRAME_MAX);
        }
        _this->living_thing_ptr->Status = MOVING;
    break;
    case SDL_KEYUP:
        switch (temp_event.key.keysym.sym)
        {
        case SDLK_w:
            d = UP;
            break;
        case SDLK_a:
            d = LEFT;
            break;
        case SDLK_d:
            d = RIGTH;
            break;
        case SDLK_s:
            d = DOWN;

            break;
        case SDLK_ESCAPE:
            //isRunning = false;
        default:
            break;
        }
        _this->living_thing_ptr->Velocity->X = 0;
        _this->living_thing_ptr->Velocity->Y = 0;
        _this->living_thing_ptr->Status = IDLE;
        _this->living_thing_ptr->game_object_ptr->SwitchFrames(_this->living_thing_ptr->game_object_ptr,_this->living_thing_ptr->Frames[IDLE][d],LIVING_THING_FRAME_MAX);
    break;
    }
}


static void UpdateDataCore(void* _this_obj)
{

}


static void RenderCore(void* _this_obj)
{
    PRole _this=(PRole)_this_obj;
    GameCoreProcessInterface_Render(_this->living_thing_ptr);
}

PRole NewRole(void)
{
    PRole temp=(PRole)malloc(sizeof(Role));
    temp->living_thing_ptr=NewLivingThing();
    temp->HandleEvent = HandleEventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;

    int i,j,k,index,t,t_back;
    i=j=k=index=t=t_back=0;
    char buffer[200],word[10],frame1[10],frame2[10],frame3[10],frame4[10],frame5[10],frame6[10],frame7[10],frame8[10];
    FILE* fp = fopen("resource/role/img.rol","r");
    do
    {
        while( NULL != fgets(buffer,200,fp) && j<DIRECTION_ENUM_MAX )
        {
            index =0;
            k=0;

            sscanf(buffer,"%s %s %s %s %s %s %s %s",frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8);
            DebugTools_PrintDebugInfo("%s %s %s %s %s %s %s %s",frame1,frame2,frame3,frame4,frame5,frame6,frame7,frame8);
            temp->living_thing_ptr->Frames[0][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame2),GetTotalSurface(),atoi(frame1));
            temp->living_thing_ptr->Frames[0][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame4),GetTotalSurface(),atoi(frame3));
            temp->living_thing_ptr->Frames[0][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame6),GetTotalSurface(),atoi(frame5));
            temp->living_thing_ptr->Frames[0][j][k++] = GetTransparentTexture(GetTotalSurface(),atoi(frame8),GetTotalSurface(),atoi(frame7));
            DisPlayTexture(GetRenderer(),temp->living_thing_ptr->Frames[0][j][k-1]);

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
