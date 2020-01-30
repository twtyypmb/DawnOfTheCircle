#include "Rect.h"
#include <stdlib.h>

PRect NewRect()
{
	PRect temp = (PRect)malloc(sizeof(PRect));
	temp->position = NewPosition();
	temp->size = NewSize();
	return temp;
}

// 初始化,只复制值
PRect NewRectPS(PPosition position, PSize size)
{
	PRect temp = NewRect();
	temp->position->X = position->X;
	temp->position->Y = position->Y;
	temp->size->Width = size->Width;
	temp->size->Height = size->Height;
	return temp;
}

void FreeRect(PRect rect_ptr)
{
	if (rect_ptr == NULL)
	{
		return;
	}

	if (rect_ptr->position != NULL)
	{
		free(rect_ptr->position);
	}

	if (rect_ptr->size != NULL)
	{
		free(rect_ptr->size);
	}

	free(rect_ptr);
	rect_ptr = NULL;
}