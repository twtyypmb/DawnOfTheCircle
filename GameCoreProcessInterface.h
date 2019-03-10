
#ifndef GAME_CORE_PROCESS_INTERFACE_H
#define GAME_CORE_PROCESS_INTERFACE_H

#include "Position.h"


/**

����ͳһ����Ϸ���½ӿ�

**/

#define GameCoreProcessInterface_GetPosition(p) p->GetPosition(p)
#define GameCoreProcessInterface_ProcessLoop(p) p->ProcessLoop(p)
#define GameCoreProcessInterface_HandleEnvent(p) p->HandleEnvent(p)
#define GameCoreProcessInterface_UpdateData(p) p->UpdateData(p)
#define GameCoreProcessInterface_Render(p) p->Render(p)

typedef PPosition (* GetPositionFun)(void* _this);
typedef void (* HandleEnventFun)( void* _this );
typedef void (* UpdateDataFun)( void* _this );
typedef void (* RenderFun)( void* _this );


#endif // GAME_CORE_PROCESS_INTERFACE_H
