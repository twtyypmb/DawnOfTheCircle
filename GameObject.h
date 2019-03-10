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

// ��Ϸ�еĶ��󣬲�Ҫֱ��ʵ��������Ϊ��֪��ͼ����Դ

typedef struct
{

    SDL_Texture*  texture;
    PPosition _position_ptr;
    PPosition Velocity;
    GameObjectDirectionEnum Direction;
    GameObjectStatusEnum GameObjectStatus;
    SDL_Texture* Frames[2][GAME_OBJECT_MAX_FRAME];// �ж���״̬���ж���frame

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
