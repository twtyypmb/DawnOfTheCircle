#include <stdio.h>
#include <stdlib.h>
#include "Game.h"


/*
静态方法用下划线作为命名空间


static作用

    用于顶层变量前，可将变量全局化，可在其他文件中以extern引用
    用于函数体内部变量前，可将变量静态化，退出函数体，值依然存在
    用于函数实现之前，可将函数私有化，防止其他文件调用

结构体定义约定
    以下划线开头小写视为隐藏字段，禁止读写 Under Score Case
    以纯小写视为只读字段Under Score Case
    大驼峰风格视为可读可写字段upper camel case
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
