#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Map.h"


/*
static����

���ڶ������ǰ���ɽ�����ȫ�ֻ������������ļ�����extern����
���ں������ڲ�����ǰ���ɽ�������̬�����˳������壬ֵ��Ȼ����
���ں���ʵ��֮ǰ���ɽ�����˽�л�����ֹ�����ļ�����

�ṹ�嶨��Լ��
���»��߿�ͷ��Ϊ˽���ֶΣ���ֱֹ���޸�
�Ժ���ָ��ķ�ʽʵ�ֳ�Ա����

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
