#include "CommonResource.h"
#include "DebugTools.h"

extern SDL_Window* _window;
extern SDL_Renderer* _renderer;
extern SDL_Texture* _total_image;
extern SDL_Texture* _total_image_back;
extern SDL_Texture* _shock_wave[4];
extern SDL_Texture* _doors;
extern SDL_Texture* _game_log;
extern SDL_Texture* _game_over;
extern SDL_Texture* _the_end;
extern SDL_Texture* _description;

bool InitResource( void )
{
    if( 0== SDL_Init( SDL_INIT_EVERYTHING) )
    {
        PrintDebugInfo(" engin initialized..\n");
        return true;
    }
    else
    {
        return false;
    }
}

SDL_Window* GetWindow( void )
{
    if( _window == NULL)
    {
        _shock_wave[0]=NULL;



        _window = SDL_CreateWindow("title",300,100,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
        if(_window)
        {
            PrintDebugInfo("create window success");
            return _window;
        }
        else
        {
            return NULL;
        }
    }

    return _window;
}

SDL_Renderer* GetRenderer(void )
{
    if(NULL== _renderer)
    {
        _renderer = SDL_CreateRenderer(GetWindow(),-1,0);

        if(_renderer)
        {
            SDL_SetRenderDrawColor(_renderer,255,255,255,255);
            PrintDebugInfo("create renderer success");
            return _renderer;
        }
        else
        {
            return NULL;
        }
    }

    return _renderer;
}


// 加载图片公共方法
SDL_Texture* LoadImage(const char* path)
{
    SDL_Surface * temp_surface = IMG_Load(path);
    if(NULL == temp_surface)
    {
        return NULL;
    }
    SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(GetRenderer(),temp_surface);
    SDL_FreeSurface(temp_surface);
    return temp_texture;
}


// 初始化公共资源


SDL_Texture* GetTotalImage()
{
    if(NULL==_total_image)
    {
        _total_image= LoadImage("resource/image/total_image.bmp");
    }
    return _total_image;
}
SDL_Texture* GetTotalImageBack()
{
    if(NULL==_total_image)
    {
       _total_image_back = LoadImage("resource/image/total_image_back.bmp");
    }
    return _total_image;
}

SDL_Texture* GetTotalImageNumber( int number )
{
    //SDL_BlitSurface()
}

SDL_Texture** GetShockWave()
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

SDL_Texture* GetDescription()
{
    if(NULL==_description)
    {
       _description = LoadImage("resource/image/description.jpg");
    }
    return _description;
}

SDL_Texture* GetDoors()
{
    if(NULL==_doors)
    {
       _doors = LoadImage("resource/image/doors.jpg");
    }
    return _description;
}

SDL_Texture* GetGameLogo()
{
    if(NULL==_game_log)
    {
       _game_log = LoadImage("resource/image/game_logo.jpg");
    }
    return _game_log;
}

SDL_Texture* GetTheEnd()
{
    if(NULL==_the_end)
    {
       _the_end = LoadImage("resource/image/the_end.jpg");
    }
    return _the_end;
}


SDL_Texture* GetGameOver()
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
    SDL_free(_total_image);
    SDL_free(_total_image_back);

    if(NULL != _renderer)
    {
        SDL_DestroyRenderer(_renderer);
        _renderer= NULL;
    }

    if(NULL != _window)
    {
        SDL_DestroyWindow(_window);
        _window= NULL;
    }
}


