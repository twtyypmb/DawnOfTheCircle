#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

int main()
{
    PGame game_ptr = NewGame();
    game_ptr->Init(game_ptr);
    int i = 0;
    int frame_during = 0;
    while(game_ptr->is_running)
    {
        i = SDL_GetTicks();
        game_ptr->HandleEnvent(game_ptr);
        game_ptr->UpdateData(game_ptr);

        frame_during =SDL_GetTicks() - i;
        if(frame_during <1.0* 1000 / GAME_FPS)
        {
            SDL_Delay(1.0* 1000 / GAME_FPS - frame_during);
        }
        game_ptr->Render(game_ptr);
    }

    FreeGame(game_ptr);
    game_ptr=NULL;
    return 0;
}
