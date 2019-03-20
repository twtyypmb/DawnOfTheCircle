#include <stdlib.h>
#include "LivingThing.h"
#include "GameCoreProcessInterface.h"
#include "CommonResource.h"

static void HandleEventCore(void* obj)
{
    PLivingThing _this = (PLivingThing)obj;
    GameCoreProcessInterface_HandleEvent(_this->game_object_ptr);

}

static void UpdateDataCore(void* obj)
{
    PLivingThing _this = (PLivingThing)obj;
    GameCoreProcessInterface_UpdateData(_this->game_object_ptr);
}
static void RenderCore(void* obj)
{
    PLivingThing _this = (PLivingThing)obj;
    GameCoreProcessInterface_Render(_this->game_object_ptr);
}

PLivingThing NewLivingThing(void)
{
    PLivingThing temp=(PLivingThing)malloc(sizeof(LivingThing));
    temp->game_object_ptr = NewGameObject();
    temp->HandleEvent = HandleEventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    temp->Direction = UP;
    temp->Status = IDLE;
    temp->Velocity = NewPosition();

    return temp;
}


void FreeLivingThing(PLivingThing obj)
{
    FreeGameObject(obj->game_object_ptr);
    FreeLivingThing(obj);
}
