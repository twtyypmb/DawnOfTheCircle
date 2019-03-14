#include "CommonResource.h"
#include "DebugTools.h"
#include "string.h"
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
SDL_Surface * total_surface;
SDL_Surface * total_back_surface;
SDL_Surface* single_total_surface[SINGLE_TOTAL_SURFACE_MAX_LENGTH];


void FreeSDLSurface(SDL_Surface *p){if(p!=NULL)SDL_FreeSurface(p);}
void FreeSDLTexture(SDL_Texture *p){if(p!=NULL)SDL_DestroyTexture(p);}


bool InitResource( void )
{
    memset(single_total_surface,0,SINGLE_TOTAL_SURFACE_MAX_LENGTH);
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


SDL_Surface* GetTotalSurface()
{
    if(NULL == total_surface)
    {
        total_surface = IMG_Load("resource/image/total.bmp");

    }
    return total_surface;
}

SDL_Surface* GetTotalBackSurface()
{
    if(NULL == total_back_surface)
    {
        total_back_surface = IMG_Load("resource/image/total_back.bmp");

    }
    return total_back_surface;
}

SDL_Texture* GetTransparentTexture( int number )
{
//    Uint32 key =SDL_MapRGB(GetTotalBackSurface()->format,0,0,0);
//    SDL_SetColorKey(GetTotalBackSurface(),1,key);
//    return SDL_CreateTextureFromSurface(GetRenderer(),GetTotalBackSurface());
    if( number >= SINGLE_TOTAL_SURFACE_MAX_LENGTH )
    {
        return NULL;
    }

    if(NULL == single_total_surface[number])
    {
        // 读取32*32整体图片和轮廓图片
        // 把back图像忽略颜色(0x0,0x0,0x0)贴图到正常图像，得到背景颜色(0x80,0xFF,0xFF)的中间图片
        // 中间图片忽略颜色(0x80,0xFF,0xFF)

        // 创建新的临时图片区32*32
        SDL_Surface* temp_surface = SDL_CreateRGBSurface( 0,OBJECT_WIDTH,OBJECT_HEIGHT,32,RMASK, GMASK,BMASK, AMASK );
        SDL_Surface* temp_surface_back = SDL_CreateRGBSurface( 0,OBJECT_WIDTH,OBJECT_HEIGHT,32,RMASK, GMASK,BMASK, AMASK );

        if(true)
        {
            SDL_Rect rect,dst;
            int i,j;
            Uint32 colorkey = 0;
            rect.x = number % 11 * OBJECT_WIDTH;
            rect.y = number / 11 * OBJECT_HEIGHT;
            dst.x = dst.y=0;
            dst.w = rect.w = OBJECT_WIDTH;
            dst.h = rect.h = OBJECT_HEIGHT;

            i=SDL_BlitSurface(GetTotalSurface(),&rect,temp_surface,NULL);

            j=SDL_BlitSurface(GetTotalBackSurface(),&rect,temp_surface_back,NULL);

            // 从整体资源图片的拷贝
            if( i== 0 && j == 0 )
            {

                colorkey=SDL_MapRGB(temp_surface_back->format,0,0,0);
                //SDL_MapRGB可以将我们给定的rgb映射成传入surface的像素格式
                //设置青色透明
                //SDL_SRCCOLORKEY标志保证我们在blit表面的时候是设置透明的
                if(SDL_SetColorKey(temp_surface_back,1,colorkey) != 0)
                {
                    PrintDebugInfo("set temp_surface_back color key failed");
                }

                // 拷贝到临时图片中
                if( 0 != SDL_BlitSurface(temp_surface_back,&dst,temp_surface,&dst) )
                {
                    PrintDebugInfo("SDL_BlitSurface temp_surface_back failed");
                }

                //return SDL_CreateTextureFromSurface(GetRenderer(),temp_surface);

                colorkey=SDL_MapRGB(temp_surface->format,0x80,0xFF,0xFF);
                if(0 == SDL_SetColorKey(temp_surface,1,colorkey))
                {
                    PrintDebugInfo("SDL_SetColorKey temp_surface color key failed");
                }


                single_total_surface[number] = SDL_CreateTextureFromSurface(GetRenderer(),temp_surface);
            }
            else
            {
                return NULL;
            }
        }
        FreeSDLSurface(temp_surface);
        FreeSDLSurface(temp_surface_back);
        temp_surface=temp_surface_back=NULL;

    }


    return single_total_surface[number];


}


SDL_Texture* GetTotalImageBack()
{
    if(NULL==_total_image)
    {
       _total_image = LoadImage("resource/image/total_image_back.bmp");
    }
    return _total_image;
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
    return _doors;
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
    //SDL_free(_total_image_back);

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


