#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "GameProcessInterface.h"
#include "GameObject.h"
#include "Position.h"
#include "BGM.h"

typedef struct _Map Map;
typedef Map* PMap;

typedef bool (*InitMapFun)(PMap _this,int map_number);



struct _Map
{
    char MapName[50];
    PGameObject** _monsters_ptr;
    PBGM BGMPtr;
    PPosition UpInitialPositionPtr;
    PPosition DownInitialPositionPtr;

    InitMapFun Init;
    HandleEnventFun HandleEnvent;
    UpdateDataFun UpdateData;
    RenderFun Render;
};

#endif // MAP_H

PMap NewMap( void );
void FreeMap( PMap map_ptr );
