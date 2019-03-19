#include "DebugTools.h"

#include <stdio.h>
#include <stdarg.h>

void DebugTools_PrintDebugInfo(char* cmd,...)
{
    #ifdef DEBUG_GAME

    va_list args;       //定义一个va_list类型的变量，用来储存单个参数
    va_start(args,cmd); //使args指向可变参数的第一个参数
    vprintf(cmd,args);  //必须用vprintf等带V的
    va_end(args);       //结束可变参数的获取

    #endif // DEBUG_GAME


}

void DebugTools_PrintDebugLine(char * str)
{
    #ifdef DEBUG_GAME
    printf("%s\n",str);
    #endif // DEBUG_GAME
}

void DisPlayTexture(SDL_Renderer* render,SDL_Texture* texture)
{
    #ifdef DEBUG_GAME
    SDL_Rect rect;
    rect.x=rect.y=0;
    rect.w=rect.h=64;
    SDL_RenderCopy(render,texture,NULL,&rect);
    SDL_RenderPresent(GetRenderer());
    #endif // DEBUG_GAME
}
