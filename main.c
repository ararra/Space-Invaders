#include "main.h"


int main()
{
    bool game_is_running;

    initialize_SDL();



    while (game_is_running)
    {
        
    }
    

}

void initialize_SDL()
{
    if(!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO| SDL_INIT_GAMEPAD))
    {
        SDL_Log("Failled to initialize. Error:%s",SDL_GetError());
        exit(EXIT_FAILURE);
    }


    
}
