#include "main.h"


int main()
{
    bool game_is_running;
    SDL_Event event;

    initialize_SDL();



    while (game_is_running)
    {        
        // Events

        while (SDL_PollEvent(&event))
        {
            if (&event.type == SDL_EVENT_QUIT)
            {
                game_is_running = false;
            }
            
        }
        
        // Logic
        // Render
        SDL_RenderClear(g_game.renderer);
        SDL_RenderPresent(g_game.renderer);
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
