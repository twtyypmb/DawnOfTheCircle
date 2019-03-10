#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "GameCoreProcessInterface.h"
#include "SDL.h"
#include "SDL_image.h"

#define GAME_OBJECT_MAX_FRAME 4

typedef enum
{
    UP,
    LEFT,
    DOWN,
    RIGTH
}GameObjectDirectionEnum;

typedef enum
{
    IDLE,
    MOVING
}GameObjectStatusEnum;

typedef SDL_Event (* GetEventFun)( void );

// 游戏中的对象，不要直接实例化，因为不知道图像来源

typedef struct
{

    SDL_Texture*  texture;
    PPosition _position_ptr;
    PPosition Velocity;
    GameObjectDirectionEnum Direction;
    GameObjectStatusEnum GameObjectStatus;
    SDL_Texture* Frames[2][GAME_OBJECT_MAX_FRAME];// 有多少状态就有多少frame

    char Name[10];
    int _speed;
    int _current_frame;

    GetEventFun GetEvent;
    GetPositionFun GetPosition;
    HandleEnventFun HandleEnvent;
    UpdateDataFun UpdateData;
    RenderFun Render;
}GameObject;

typedef GameObject* PGameObject;

PGameObject NewGameObject( SDL_Texture*  texture,GetEventFun GetEvent );
void FreeGameObject(PGameObject);

#endif // GAME_OBJECT_H
