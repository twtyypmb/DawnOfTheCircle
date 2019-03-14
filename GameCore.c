#include "GameCore.h"
#include <stdio.h>

static bool InitCore( PGameCore _this )
{

    GameCore* this = (GameCore*)_this;

    this->_is_running = true;

    return true;

    int i = 0;
    for(; i < MAP_MAX_COUNT;i++)
    {
        _this->_map_ptr_arr[i] = NewMap(i);
    }

    this->_is_running = true;

    return true;
}

static bool IsRunningCore( PGameCore _this )
{
    GameCore* this = (GameCore*)_this;
    return this->_is_running;
}


static void HandleEnventCore(void* _this)
{
    PGameCore this = (PGameCore)_this;

    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        this->_is_running = false;
        break;
    default:
        break;
    }

}

static void UpdateDataCore(void* this)
{
    PGameCore _this = (PGameCore)this;
    _this->Rect.w = 100;
    _this->Rect.h = 100;
    _this->Rect.x = _this->count;

    PrintDebugInfo("%d\n",_this->count++);
}

static void RenderCore(void* _this)
{
    PGameCore this = (PGameCore)_this;
    SDL_RenderClear(GetRenderer());
    SDL_RenderCopy(GetRenderer(),GetShockWave()[0],NULL,NULL);
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

        _this->HandleEnvent(_this);
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
    temp->HandleEnvent = HandleEnventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    temp->ProcessLoop = ProcessLoopCore;
    temp->count=0;

    return temp;

}

void FreeGameCore(PGameCore config)
{

    SDL_Quit();

    free(config);
}

