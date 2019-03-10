#include "Game.h"
#include "GameCore.h"

static void ProcessLoopCore( void * object)
{
//    PGame _this = (PGame)object;
    InitResource();
    PGameCore game_ptr = NewGameCore();
    game_ptr->Init(game_ptr);
    game_ptr->ProcessLoop(game_ptr);
    FreeGameCore(game_ptr);
    game_ptr=NULL;
}

static void InitGameCore(PGame _this)
{

}

PGame NewGame( void )
{
    PGame temp = (PGame)malloc(sizeof(Game));
    temp->ProcessLoop = ProcessLoopCore;

    return temp;
}

void FreeGame(PGame game_ptr)
{
    FreeAllCommonResource();

    free(game_ptr);
}
