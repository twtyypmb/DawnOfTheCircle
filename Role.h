#ifndef ROLE_H
#define ROLE_H

#include "GameObject.h"
#include "LivingThing.h"

typedef struct
{
    PLivingThing living_thing_ptr;


    GetPositionFun GetPosition;
    HandleEventFun HandleEvent;
    UpdateDataFun UpdateData;
    RenderFun Render;
}Role;
typedef Role* PRole;


PRole NewRole(void);
void FreeRole(PRole);

#endif // ROLE_H
