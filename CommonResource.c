#include "CommonResource.h"

// 加载图片公共方法
SDL_Texture* LoadImage(SDL_Renderer* renderer,const char* path)
{
    SDL_Surface * temp_surface = IMG_Load(path);
    SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(renderer,temp_surface);
    SDL_FreeSurface(temp_surface);
    return temp_texture;
}


// 初始化公共资源
void InitCommonResource(SDL_Renderer* renderer)
{
    total_image= LoadImage(renderer,"resource/image/total_image");
    total_image_back= LoadImage(renderer,"resource/image/total_image_back");

}


// 释放公共资源
void DisposeCommonResource( void )
{
    SDL_free(total_image);
    SDL_free(total_image_back);
}


