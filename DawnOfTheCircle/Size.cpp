#include "Size.h"
#include <stdlib.h>


PSize NewSize()
{
	PSize temp = (PSize)malloc(sizeof(Size));
	temp->Width = temp->Height = 0;

	return temp;
}

PSize NewSizeWH(int width, int height)
{
	PSize temp = NewSize();
	temp->Width = width;
	temp->Width = height;
	return temp;
}


void FreeSize(PSize position_ptr)
{
	free(position_ptr);
}
