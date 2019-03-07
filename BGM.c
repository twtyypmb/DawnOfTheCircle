#include "BGM.h"
#include "stdlib.h"

BGM* NewBGM( void )
{
    BGM * temp = (BGM *)malloc(sizeof(BGM));
    temp->music_volume = 0.1;
    return temp;
}

void FreeBGM(BGM* bgm)
{
    free(bgm);
}
