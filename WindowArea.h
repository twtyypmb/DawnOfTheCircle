#ifndef WINDOW_AREA_H
#define WINDOW_AREA_H

#include <SDL_image.h>

typedef void (* ClearFun)(void* _this);



typedef struct
{
    SDL_Surface* area;
    int window_number;
    int position[2];
    int width_height[2];

    ClearFun Clear;

}WindowArea;

typedef WindowArea* PWindowArea;

PWindowArea NewWindowArea();
void FreeWindowArea(PWindowArea window_area);

#endif // WINDOW_AREA_H
