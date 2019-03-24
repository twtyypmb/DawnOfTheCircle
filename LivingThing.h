#ifndef LIVING_THING_H
#define LIVING_THING_H

#include "GameObject.h"
#define DIRECTION_ENUM_MAX              4
#define STATUS_ENUM_MAX                 2
#define LIVING_THING_FRAME_MAX           4

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

typedef SDL_Event* (*GetEvnetFun)( void );

typedef struct
{
    PGameObject game_object_ptr;
    PPosition Velocity;
    GameObjectDirectionEnum Direction;
    GameObjectStatusEnum Status;
    SDL_Texture* Frames[STATUS_ENUM_MAX][DIRECTION_ENUM_MAX][LIVING_THING_FRAME_MAX];// 有多少状态就有多少frame

    GetEvnetFun GetEvent;
    HandleEventFun HandleEvent;
    UpdateDataFun UpdateData;
    RenderFun Render;
}LivingThing;

typedef LivingThing* PLivingThing;

PLivingThing NewLivingThing( GetEvnetFun ef );
void FreeLivingThing(PLivingThing obj);

#endif // LIVING_THING_H
