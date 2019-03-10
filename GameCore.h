#ifndef GAME_CORE_H
#define GAME_CORE_H

#include "CommonResource.h"
#include "GameObject.h"
#include "FloorGround.h"
#include "BGM.h"
#include "GameProcessInterface.h"
#include "stdlib.h"
#include <stdbool.h>
#include "Map.h"

#define GAME_FPS 60
#define MAP_MAX_COUNT 23



typedef struct _GameCore GameCore;
typedef GameCore* PGameCore;
typedef bool (*InitFun)(PGameCore _this);
typedef bool (*IsRunningFun)(PGameCore _this);

struct _GameCore
{
    bool _is_running;
    PMap _map_ptr_arr[MAP_MAX_COUNT];

    SDL_Rect Rect;

    long long count;


    InitFun Init;
    ProcessLoopFun ProcessLoop;
    IsRunningFun IsRunning;
    HandleEnventFun HandleEnvent;
    UpdateDataFun UpdateData;
    RenderFun Render;

};

PGameCore NewGameCore( void );
void FreeGameCore(PGameCore p_game);

#endif // GAME_CORE_H
