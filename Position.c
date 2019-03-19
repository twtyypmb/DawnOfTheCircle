#include "Position.h"
#include <stdlib.h>

void SetNewPosition(PPosition origin, PPosition dest)
{
    origin->X = dest->X;
    origin->Y = dest->Y;

}

PPosition NewPosition()
{
     PPosition temp =(PPosition)malloc(sizeof(Position));
     temp->X=temp->Y=0;
    return temp;
}

void FreePosition(PPosition position_ptr)
{
    free(position_ptr);
}
