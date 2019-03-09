#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Map.h"


/*
static作用

用于顶层变量前，可将变量全局化，可在其他文件中用extern引用
用于函数体内部变量前，可将变量静态化，退出函数体，值依然存在
用于函数实现之前，可将函数私有化，防止其他文件调用

结构体定义约定
以下划线开头视为私有字段，禁止直接修改
以函数指针的方式实现成员函数

*/

int main()
{
    PMap map_ptr = NewMap();
    map_ptr->Init(map_ptr,0);

    PGame game_ptr = NewGame();
    game_ptr->Init(game_ptr);
    int i = 0;
    int frame_during = 0;
    while(game_ptr->IsRunning(game_ptr))
    {
        i = SDL_GetTicks();

        GameProcessInterface_HandleEnvent(game_ptr);
        GameProcessInterface_UpdateData(game_ptr);

        frame_during =SDL_GetTicks() - i;
        if(frame_during <1.0* 1000 / GAME_FPS)
        {
            SDL_Delay(1.0* 1000 / GAME_FPS - frame_during);
        }
        GameProcessInterface_Render(game_ptr);
    }

    FreeGame(game_ptr);
    game_ptr=NULL;
    return 0;
}
