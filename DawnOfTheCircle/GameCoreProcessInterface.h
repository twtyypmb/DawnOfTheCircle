
#ifndef GAME_CORE_PROCESS_INTERFACE_H
#define GAME_CORE_PROCESS_INTERFACE_H

#include "Rect.h"


/**

定义统一的游戏更新接口

**/

#define GameCoreProcessInterface_GetRect(p) p->GetRect(p)
#define GameCoreProcessInterface_ProcessLoop(p) p->ProcessLoop(p)
#define GameCoreProcessInterface_HandleEvent(p) p->HandleEvent(p)
#define GameCoreProcessInterface_UpdateData(p) p->UpdateData(p)
#define GameCoreProcessInterface_Render(p) p->Render(p)

typedef PRect (* GetRectFun)(void* _this);
typedef void (* HandleEventFun)( void* _this );
typedef void (* UpdateDataFun)( void* _this );
typedef void (* RenderFun)( void* _this );


#endif // GAME_CORE_PROCESS_INTERFACE_H
