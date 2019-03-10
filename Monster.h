#ifndef MONSTER_H
#define MONSTER_H

#include "GameObject.h"

typedef struct
{
    PGameObject _game_object_ptr;
    int event_number;

    GetPositionFun GetPosition;
    HandleEnventFun HandleEnvent;
    UpdateDataFun UpdateData;
    RenderFun Render;

}Monster;

typedef Monster* PMonster;

PMonster NewMonster(int monster_number );
void FreeMonster(PMonster);

#endif // MONSTER_H

