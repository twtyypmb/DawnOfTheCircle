#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "GameProcessInterface.h"
#include "GameObject.h"
#include "Position.h"
#include "BGM.h"

#define MAP_MAX_ROW 100
#define MAP_MAX_COL 100

typedef struct _Map Map;
typedef Map* PMap;

typedef int (* GetMapRowFun)(PMap _this);
typedef int (* GetMapColFun)(PMap _this);


struct _Map
{
    char MapName[50];
    PGameObject _monsters_ptr[MAP_MAX_ROW][MAP_MAX_COL];

    int _map_row;
    int _map_col;


    PBGM BGMPtr;
    PPosition UpInitialPositionPtr;
    PPosition DownInitialPositionPtr;
    GetMapRowFun GetMapRow;
    GetMapColFun GetMapCol;


    HandleEventFun HandleEvent;
    UpdateDataFun UpdateData;
    RenderFun Render;
};

#endif // MAP_H

PMap NewMap( int map_number );
void FreeMap( PMap map_ptr );
