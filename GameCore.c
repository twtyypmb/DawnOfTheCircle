#include "GameCore.h"
#include <stdio.h>
#include "CommonResource.h"

static bool InitCore( PGameCore _this )
{

    GameCore* this = (GameCore*)_this;
    int i = 0;
    for(; i < MAP_MAX_COUNT;i++)
    {
        _this->_map_ptr_arr[i] = NULL;
        //_this->_map_ptr_arr[i] = NewMap(i);
    }

    this->_is_running = true;

    return true;
}

static bool IsRunningCore( PGameCore _this )
{
    GameCore* this = (GameCore*)_this;
    return this->_is_running;
}


static void HandleEventCore(void* _this_obj)
{
    PGameCore _this = (PGameCore)_this_obj;

    SDL_Event* temp_event_ptr =PollSDLEvent();
    switch(temp_event_ptr->type)
    {
    case SDL_QUIT:
        _this->_is_running = false;
        break;
    default:
        break;
    }
    GameCoreProcessInterface_HandleEvent(_this->role_ptr);
}

static void UpdateDataCore(void* this)
{
    PGameCore _this = (PGameCore)this;
    _this->Rect.w = 100;
    _this->Rect.h = 100;
    _this->Rect.x = _this->count;
    if(NULL != _this->_map_ptr_arr[_this->_current_floor])
    {
        _this->_map_ptr_arr[_this->_current_floor]->Render(_this->_map_ptr_arr[_this->_current_floor]);
    }
    _this->role_ptr->UpdateData(_this->role_ptr);
    DebugTools_PrintDebugInfo("%d\n",_this->count++);
}

static void RenderCore(void* _this_obj)
{

    PGameCore _this = (PGameCore)_this_obj;
    SDL_RenderClear(GetRenderer());
    if(NULL != _this->role_ptr)
    {
        _this->role_ptr->Render(_this->role_ptr);
    }
    //SDL_RenderCopy(GetRenderer(),GetTransparentTexture(GetTotalSurface(),28,GetTotalBackSurface(),28),NULL,NULL);
    SDL_RenderPresent(GetRenderer());
}

static void ProcessLoopCore( void * object)
{
    PGameCore _this = (PGameCore)object;
    int tick = 0;
    int frame_during = 0;
    while(_this->_is_running )
    {
        tick = SDL_GetTicks();

        _this->HandleEvent(_this);
        _this->UpdateData(_this);

        frame_during =SDL_GetTicks() - tick;
        if(frame_during < 1.0* 1000 / GAME_FPS)
        {
            SDL_Delay( 1.0* 1000 / GAME_FPS - frame_during);
        }
        _this->Render(_this);
    }
}

PGameCore NewGameCore( void )
{
    PGameCore temp = (GameCore*)malloc(sizeof(GameCore));
    temp->Init = InitCore;
    temp->IsRunning = IsRunningCore;
    temp->HandleEvent = HandleEventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    temp->ProcessLoop = ProcessLoopCore;
    temp->count=0;
    temp->_current_floor=0;
    temp->role_ptr = NewRole();
    return temp;

}

void FreeGameCore(PGameCore config)
{

    SDL_Quit();

    free(config);
}

