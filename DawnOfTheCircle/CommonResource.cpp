#include "CommonResource.h"
#include "string.h"

extern HWND _window;
extern PIMAGE _renderer;
extern PIMAGE _total_image;
extern PIMAGE _total_image_back;
extern PIMAGE _shock_wave[4];
extern PIMAGE _doors;
extern PIMAGE _game_log;
extern PIMAGE _game_over;
extern PIMAGE _the_end;
extern PIMAGE _description;
PIMAGE total_surface;
PIMAGE total_back_surface;
PIMAGE  single_total_surface[SINGLE_TOTAL_SURFACE_MAX_LENGTH];


void FreeSDLSurface(PIMAGE p){if(p!=NULL)delimage(p);}
void FreeSDLTexture(PIMAGE p){if(p!=NULL)delimage(p);}


bool InitResource( void )
{
    memset(single_total_surface,0,SINGLE_TOTAL_SURFACE_MAX_LENGTH);
	initgraph(640, 480);
	randomize();
	setrendermode(RENDER_MANUAL);
	return true;
}

HWND GetWindow( void )
{
    if( _window == NULL)
    {
		_window = getHWnd();
    }

    return _window;
}

PIMAGE GetRenderer(void )
{
    

    return _renderer;
}



// 加载图片为纹理
PIMAGE LoadImage(const char* path)
{
	getimage(_total_image, path, 0, 0);
    return _total_image;
}


// 初始化公共资源
PIMAGE GetTotalSurface()
{
    if(NULL == total_surface)
    {
        total_surface = LoadImage("resource/image/total.bmp");

    }
    return total_surface;
}

PIMAGE GetTotalBackSurface()
{
    if(NULL == total_back_surface)
    {
        total_back_surface = LoadImage("resource/image/total_back.bmp");

    }
    return total_back_surface;
}



PIMAGE GetTotalImageBack()
{
    if(NULL==_total_image)
    {
       _total_image = LoadImage("resource/image/total_image_back.bmp");
    }
    return _total_image;
}


PIMAGE* GetShockWave()
{
    if(NULL==_shock_wave[0])
    {
       _shock_wave[0] = LoadImage("resource/image/shock_wave_0.jpg");
       _shock_wave[1] = LoadImage("resource/image/shock_wave_1.jpg");
       _shock_wave[2] = LoadImage("resource/image/shock_wave_2.jpg");
       _shock_wave[3] = LoadImage("resource/image/shock_wave_3.jpg");
    }
    return _shock_wave;
}

PIMAGE GetDescription()
{
    if(NULL==_description)
    {
       _description = LoadImage("resource/image/description.jpg");
    }
    return _description;
}

PIMAGE GetDoors()
{
    if(NULL==_doors)
    {
       _doors = LoadImage("resource/image/doors.jpg");
    }
    return _doors;
}

PIMAGE GetGameLogo()
{
    if(NULL==_game_log)
    {
       _game_log = LoadImage("resource/image/game_logo.jpg");
    }
    return _game_log;
}

PIMAGE GetTheEnd()
{
    if(NULL==_the_end)
    {
       _the_end = LoadImage("resource/image/the_end.jpg");
    }
    return _the_end;
}


PIMAGE GetGameOver()
{
    if(NULL==_game_over)
    {
       _game_over = LoadImage("resource/image/game_over.jpg");
    }
    return _game_over;
}


// 释放公共资源
void FreeAllCommonResource( void )
{
    delimage(_total_image);
    //SDL_free(_total_image_back);

    if(NULL != _renderer)
    {
		delimage(_renderer);
        _renderer= NULL;
    }

    if(NULL != _window)
    {
		/*delimage(_window);
        _window= NULL;*/
    }
}


//SDL_Event* GetSDLEvnet( void )
//{
//    return &event;
//}
//
//SDL_Event* PollSDLEvent( void )
//{
//    SDL_PollEvent(&event);
//    return &event;
//}
