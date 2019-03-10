#include <stdio.h>
#include <stdlib.h>
#include "Game.h"


/*
static作用

    用于顶层变量前，可将变量全局化，可在其他文件中以extern引用
    用于函数体内部变量前，可将变量静态化，退出函数体，值依然存在
    用于函数实现之前，可将函数私有化，防止其他文件调用

结构体定义约定
    以下划线开头视为私有字段，禁止直接修改
    以函数指针的方式实现成员函数

*/
#include "CommonResource.h"
int main()
{

    PGame game_ptr = NewGame();
    game_ptr->ProcessLoop(game_ptr);
    FreeGame(game_ptr);
    game_ptr=NULL;
    return 0;
}
