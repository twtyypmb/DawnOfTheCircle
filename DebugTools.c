#include "DebugTools.h"

#include <stdio.h>
#include <stdarg.h>

void DebugTools_PrintDebugInfo(char* cmd,...)
{
    #ifdef DEBUG_GAME

    va_list args;       //����һ��va_list���͵ı������������浥������
    va_start(args,cmd); //ʹargsָ��ɱ�����ĵ�һ������
    vprintf(cmd,args);  //������vprintf�ȴ�V��
    va_end(args);       //�����ɱ�����Ļ�ȡ

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
