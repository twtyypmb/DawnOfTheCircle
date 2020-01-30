#ifndef RECT_H
#define RECT_H

#include "Position.h"
#include "Size.h"


typedef struct
{
	PPosition position;
	PSize size;
}Rect;

typedef Rect* PRect;


PRect NewRect();
PRect NewRectPS(PPosition position, PSize size);

void FreeRect(PRect rect_ptr);
#endif // RECT_H

