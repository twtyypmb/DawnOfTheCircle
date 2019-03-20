#ifndef MONSTER_H
#define MONSTER_H

#include "LivingThing.h"

typedef struct
{
    PLivingThing living_thing_ptr;
    int event_number;

    GetPositionFun GetPosition;
    HandleEventFun HandleEvent;
    UpdateDataFun UpdateData;
    RenderFun Render;

}Monster;

typedef Monster* PMonster;

PMonster NewMonster(int monster_number );
void FreeMonster(PMonster);

#endif // MONSTER_H

