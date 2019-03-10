#ifndef GAME_H
#define GAME_H

#include "GameProcessInterface.h"
#include "CommonResource.h"


typedef struct
{
    ProcessLoopFun ProcessLoop;
}Game;

typedef Game* PGame;

PGame NewGame( void );
void FreeGame(PGame p_game);
#endif // GAME_H
