#ifndef BGM_H
#define BGM_H

typedef struct
{
    int music_number;
    int cycle_flag;
    float music_volume;
    int play_position[4];
}BGM;

typedef BGM* PBGM;

PBGM NewBGM( int _music_number );
void FreeBGM(PBGM bgm);
#endif // BGM_H
