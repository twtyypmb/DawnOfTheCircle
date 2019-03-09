#include "Game.h"
#include <stdio.h>

static bool InitCore( PGame _this )
{
    Game* this = (Game*)_this;
    this->texture = LoadImage(this->_renderer,"resource/image/0.jpg");

    this->_is_running = true;

    return true;
}

static bool IsRunningCore( PGame _this )
{
    Game* this = (Game*)_this;
    return this->_is_running;
}


static void HandleEnventCore(void* _this)
{
    PGame this = (PGame)_this;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        this->_is_running = false;
        break;
    default:
        break;
    }

}

static void UpdateDataCore(void* _this)
{
    PGame this = (PGame)_this;
    this->Rect.w = 100;
    this->Rect.h = 100;
    this->Rect.x = this->count;
    printf("%d\n",this->count++);
}

static void RenderCore(void* _this)
{
    PGame this = (PGame)_this;
    SDL_RenderClear(this->_renderer);
    SDL_RenderCopy(this->_renderer,this->texture,NULL,&(this->Rect));
    SDL_RenderPresent(this->_renderer);
}

PGame NewGame( void )
{
    PGame temp = (Game*)malloc(sizeof(Game));
    temp->Init = InitCore;
    temp->IsRunning = IsRunningCore;
    temp->HandleEnvent = HandleEnventCore;
    temp->UpdateData = UpdateDataCore;
    temp->Render = RenderCore;
    do
    {

        if( 0== SDL_Init( SDL_INIT_EVERYTHING) )
        {
            printf(" engin initialized..\n");
        }
        else
        {
            break;
        }

        temp->_window = SDL_CreateWindow("title",300,100,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
        if(temp->_window)
        {
            printf("create window success");
        }
        else
        {
            break;
        }

        temp->_renderer = SDL_CreateRenderer(temp->_window,-1,0);

        if(temp->_renderer)
        {
            SDL_SetRenderDrawColor(temp->_renderer,255,255,255,255);
            printf("create renderer success");
        }
        else
        {
            break;
        }

        return temp;

    }while(0);


    FreeGame(temp);



    return NULL;

}

void FreeGame(PGame config)
{
    if(config->_renderer)
    {
        SDL_DestroyRenderer(config->_renderer);
    }

    if(config->_window)
    {
        SDL_DestroyWindow(config->_window);
    }

    SDL_Quit();

    free(config);
}

