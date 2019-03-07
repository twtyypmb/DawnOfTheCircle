#include "Game.h"
#include <stdio.h>

static bool InitCore( void* _this )
{
    Game* this = (Game*)_this;

    this->texture = LoadImage(this->renderer,"resource/image/0.jpg");

    this->is_running = true;

    return true;
}


static void HandleEnventCore(void* _this)
{
    PGame this = (PGame)_this;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        this->is_running = false;
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
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer,this->texture,NULL,&(this->Rect));
    SDL_RenderPresent(this->renderer);
}

PGame NewGame( void )
{
    PGame temp = (Game*)malloc(sizeof(Game));
    temp->Init = InitCore;
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

        temp->window = SDL_CreateWindow("title",300,100,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
        if(temp->window)
        {
            printf("create window success");
        }
        else
        {
            break;
        }

        temp->renderer = SDL_CreateRenderer(temp->window,-1,0);

        if(temp->renderer)
        {
            SDL_SetRenderDrawColor(temp->renderer,255,255,255,255);
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
    if(config->renderer)
    {
        SDL_DestroyRenderer(config->renderer);
    }

    if(config->window)
    {
        SDL_DestroyWindow(config->window);
    }

    SDL_Quit();

    free(config);
}

