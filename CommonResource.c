#include "CommonResource.h"

// ����ͼƬ��������
SDL_Texture* LoadImage(SDL_Renderer* renderer,const char* path)
{
    SDL_Surface * temp_surface = IMG_Load(path);
    SDL_Texture* temp_texture = SDL_CreateTextureFromSurface(renderer,temp_surface);
    SDL_FreeSurface(temp_surface);
    return temp_texture;
}


// ��ʼ��������Դ
void InitCommonResource(SDL_Renderer* renderer)
{
    total_image= LoadImage(renderer,"resource/image/total_image");
    total_image_back= LoadImage(renderer,"resource/image/total_image_back");

}


// �ͷŹ�����Դ
void DisposeCommonResource( void )
{
    SDL_free(total_image);
    SDL_free(total_image_back);
}


