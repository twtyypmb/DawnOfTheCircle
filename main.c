#include <stdio.h>
#include <stdlib.h>
#include "Game.h"


/*
��̬�������»�����Ϊ�����ռ�


static����

    ���ڶ������ǰ���ɽ�����ȫ�ֻ������������ļ�����extern����
    ���ں������ڲ�����ǰ���ɽ�������̬�����˳������壬ֵ��Ȼ����
    ���ں���ʵ��֮ǰ���ɽ�����˽�л�����ֹ�����ļ�����

�ṹ�嶨��Լ��
    ���»��߿�ͷСд��Ϊ�����ֶΣ���ֹ��д Under Score Case
    �Դ�Сд��Ϊֻ���ֶ�Under Score Case
    ���շ�����Ϊ�ɶ���д�ֶ�upper camel case
    �Ժ���ָ��ķ�ʽʵ�ֳ�Ա����

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
