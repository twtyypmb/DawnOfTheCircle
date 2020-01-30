#ifndef POSITION_H
#define POSITION_H


typedef struct
{
    int X;
    int Y;
}Position;

typedef Position* PPosition;


PPosition NewPosition();
PPosition NewPositionXY(int x,int y);
void FreePosition(PPosition position_ptr);

#endif // POSITION_H
