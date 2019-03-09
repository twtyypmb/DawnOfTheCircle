#ifndef POSITION_H
#define POSITION_H


typedef struct
{
    int X;
    int Y;
}Position;

typedef Position* PPosition;

#endif // POSITION_H
PPosition NewPosition();

void FreePosition(PPosition position_ptr);
