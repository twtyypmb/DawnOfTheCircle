#include "DebugTools.h"
#include <stdio.h>
#include <stdarg.h>

void PrintDebugInfo(char* cmd,...)
{
    #ifdef DEBUG_GAME

    va_list args;       //����һ��va_list���͵ı������������浥������
    va_start(args,cmd); //ʹargsָ��ɱ�����ĵ�һ������
    vprintf(cmd,args);  //������vprintf�ȴ�V��
    va_end(args);       //�����ɱ�����Ļ�ȡ

    #endif // DEBUG_GAME


}
