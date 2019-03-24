#include <stdlib.h>
#include "LivingThing.h"
#include "GameCoreProcessInterface.h"
#include "CommonResource.h"

static void HandleEventCore(void* obj)
{
    PLivingThing _this = (PLivingThing)obj;
    GameObjectDirectionEnum d;
    if(_this->GetEvent!= NULL)
    {
        SDL_Event* temp_event_ptr = _this->GetEvent();
        switch(temp_event_ptr->type)
        {
        case SDL_KEYDOWN:
            switch (temp_event_ptr->key.keysym.sym)
            {
            case SDLK_w:
                _this->Velocity->Y = -1;
                d = UP;
                break;
            case SDLK_a:
                _this->Velocity->X = -1;
                d = LEFT;
                break;
            case SDLK_d:
                _this->Velocity->X = 1;
                d = RIGTH;
                break;
            case SDLK_s:
                _this->Velocity->Y = 1;
                d = DOWN;
                break;
            default:
                break;
            }
            if( _this->Status != MOVING )
            {
                _this->game_object_ptr->SwitchFrames(_this->game_object_ptr,_this->Frames[MOVING][d],LIVING_THING_FRAME_MAX);
            }
            _this->Status = MOVING;
        break;
        case SDL_KEYUP:
            switch (temp_event_ptr->key.keysym.sym)
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
            _this->Velocity->X = 0;
            _this->Velocity->Y = 0;
            _this->Status = IDLE;
            _this->game_object_ptr->SwitchFrames(_this->game_object_ptr,_this->Frames[IDLE][d],LIVING_THING_FRAME_MAX);
        break;
        }

    }

    GameCoreProcessInterface_HandleEvent(_this->game_object_ptr);

}

static void UpdateDataCore(void* obj)
{
    PLivingThing _this = (PLivingThing)obj;
    GameCoreProcessInterface_GetPosition(_this->game_object_ptr)->X+=_this->Velocity->X;
    GameCoreProcessInterface_GetPosition(_this->game_object_ptr)->Y+=_this->Velocity->Y;
    GameCoreProcessInterface_UpdateData(_this->game_object_ptr);
}
static void RenderCore(void* obj)
{
    PLivingThing _this = (PLivingThing)obj;
    GameCoreProcessInterface_Render(_this->game_object_ptr);
}

PLivingThing NewLivingThing(GetEvnetFun ef)
{
    PLivingThing temp=(PLivingThing)malloc(sizeof(LivingThing));
    temp->game_object_ptr = NewGameObject();
    temp->HandleEvent = HandleEventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    temp->Direction = UP;
    temp->Status = IDLE;
    temp->Velocity = NewPosition();
    temp->GetEvent = ef;
    return temp;
}


void FreeLivingThing(PLivingThing obj)
{
    FreeGameObject(obj->game_object_ptr);
    FreeLivingThing(obj);
}
