#ifndef COMMON_RESOURCE_H
#define COMMON_RESOURCE_H

#define SDL_MAIN_HANDLED


#include <SDL.h>
#include <SDL_image.h>


SDL_Texture* total_image;
SDL_Texture* total_image_back;
#endif // COMMON_RESOURCE_H

SDL_Texture* LoadImage(SDL_Renderer* renderer,const char* path);
void DisposeCommonResource( void );
