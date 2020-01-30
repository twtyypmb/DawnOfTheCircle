#ifndef COMMON_RESOURCE_H
#define COMMON_RESOURCE_H

#include <stdbool.h>
#include <graphics.h>

#define WINDOW_WIDTH                                800
#define WINDOW_HEIGHT                               600
#define SINGLE_TOTAL_SURFACE_MAX_LENGTH             220
#define OBJECT_WIDTH                                32
#define OBJECT_HEIGHT                               32


static HWND _window = NULL;
static PIMAGE _renderer = NULL;
//static SDL_Event event;
static PIMAGE _total_image = NULL;
static PIMAGE _total_image_back = NULL;
static PIMAGE _shock_wave[4];
static PIMAGE _doors = NULL;
static PIMAGE _game_log = NULL;
static PIMAGE _game_over = NULL;
static PIMAGE _the_end = NULL;
static PIMAGE _description = NULL;

/*******************/
bool InitResource(void);
HWND GetWindow(void);
PIMAGE GetRenderer(void);
PIMAGE GetTotalImage(void);
PIMAGE GetTransparentTexture(PIMAGE surface, int number, PIMAGE surface_back, int number_back);
PIMAGE* GetShockWave(void);
PIMAGE GetDescription(void);
PIMAGE GetDoors(void);
PIMAGE GetGameLogo(void);
PIMAGE GetTheEnd(void);
PIMAGE GetGameOver(void);
void FreeAllCommonResource(void);
PIMAGE GetTotalSurface(void);
PIMAGE GetTotalBackSurface(void);
//SDL_Event* GetSDLEvnet( void );
//SDL_Event* PollSDLEvent( void );

#endif // COMMON_RESOURCE_H


