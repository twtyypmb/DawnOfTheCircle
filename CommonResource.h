#ifndef COMMON_RESOURCE_H
#define COMMON_RESOURCE_H

#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#define WINDOW_WIDTH                                800
#define WINDOW_HEIGHT                               600
#define SINGLE_TOTAL_SURFACE_MAX_LENGTH             220
#define OBJECT_WIDTH                                32
#define OBJECT_HEIGHT                               32
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK                                       0xff000000
#define GMASK                                       0x00ff0000
#define BMASK                                       0x0000ff00
#define AMASK                                       0x000000ff
#else
#define RMASK                                       0x000000ff
#define GMASK                                       0x0000ff00
#define BMASK                                       0x00ff0000
#define AMASK                                       0xff000000
#endif


static SDL_Window* _window=NULL;
static SDL_Renderer* _renderer=NULL;
static SDL_Event event;
static SDL_Texture* _total_image = NULL;
static SDL_Texture* _total_image_back= NULL;
static SDL_Texture* _shock_wave[4];
static SDL_Texture* _doors= NULL;
static SDL_Texture* _game_log= NULL;
static SDL_Texture* _game_over= NULL;
static SDL_Texture* _the_end= NULL;
static SDL_Texture* _description= NULL;

/*******************/
bool InitResource( void );
SDL_Texture* LoadImage(const char* path);
SDL_Window* GetWindow(void );
SDL_Renderer* GetRenderer(void );
SDL_Texture* GetTotalImage(void);
SDL_Texture* GetTransparentTexture(SDL_Surface* surface, int number,SDL_Surface* surface_back, int number_back );
SDL_Texture** GetShockWave(void);
SDL_Texture* GetDescription(void);
SDL_Texture* GetDoors(void);
SDL_Texture* GetGameLogo(void);
SDL_Texture* GetTheEnd(void);
SDL_Texture* GetGameOver(void);
void FreeAllCommonResource( void );
SDL_Event GetEvnet( void );

#endif // COMMON_RESOURCE_H


