#ifndef GAME_H
#define GAME_H

#include "CommonResource.h"
#include "Role.h"
#include "FloorGround.h"
#include "BGM.h"
#include "GameProcessInterface.h"
#include "stdlib.h"
#include <stdbool.h>

#define GAME_FPS 60
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


typedef bool (*InitFun)(void* _this);

typedef struct
{


    bool is_running;
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Rect Rect;
    SDL_Texture* texture;
    int count;


    InitFun Init;
    HandleEnventFun HandleEnvent;
    UpdateDataFun UpdateData;
    RenderFun Render;

}Game;

typedef Game* PGame;


PGame NewGame( void );
void FreeGame(PGame config);

#endif // GAME_H
