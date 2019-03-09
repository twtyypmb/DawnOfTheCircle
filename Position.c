#include "Position.h"
#include <stdlib.h>

void SetNewPosition(PPosition origin, PPosition dest)
{
    origin->X = dest->X;
    origin->Y = dest->Y;

}

PPosition NewPosition()
{
    return (PPosition)malloc(sizeof(Position));
}

void FreePosition(PPosition position_ptr)
{
    free(position_ptr);
}
