#ifndef GAME_H
#define GAME_H

#include "CommonResource.h"
#include "GameObject.h"
#include "FloorGround.h"
#include "BGM.h"
#include "GameProcessInterface.h"
#include "stdlib.h"
#include <stdbool.h>

#define GAME_FPS 60
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct _Game Game;
typedef Game* PGame;
typedef bool (*InitFun)(PGame _this);
typedef bool (*IsRunningFun)(PGame _this);

struct _Game
{
    bool _is_running;
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    SDL_Rect Rect;
    SDL_Texture* texture;
    int count;


    InitFun Init;
    IsRunningFun IsRunning;
    HandleEnventFun HandleEnvent;
    UpdateDataFun UpdateData;
    RenderFun Render;

};

PGame NewGame( void );
void FreeGame(PGame p_game);

#endif // GAME_H
