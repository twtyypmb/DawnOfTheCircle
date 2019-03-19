#ifndef DEBUG_TOOLS_H
#define DEBUG_TOOLS_H

#include "SDL.h"
#include "SDL_image.h"

#define DEBUG_GAME

void DebugTools_PrintDebugInfo(char*,...);
void DebugTools_PrintDebugLine(char * str);
void DisPlayTexture(SDL_Renderer* render,SDL_Texture* texture);
#endif // DEBUG_TOOLS_H
