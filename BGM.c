#include "BGM.h"
#include "stdlib.h"

BGM* NewBGM( int _music_number )
{
    BGM * temp = (BGM *)malloc(sizeof(BGM));
    temp->music_volume = 0.1;
    temp->music_number = _music_number;
    return temp;
}

void FreeBGM(BGM* bgm)
{
    free(bgm);
}
