#include "main.h"


int main()
{
    bool game_is_running = true;
    SDL_Event event;

    initialize_SDL();



    while (game_is_running)
    {        
        // Events

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                game_is_running = false;
            }
            
        }
        
        // Logic
        // Render
        SDL_RenderClear(g_game.renderer);
        SDL_RenderPresent(g_game.renderer);


    }
    
    SDL_DestroyRenderer(g_game.renderer);
    SDL_DestroyWindow(g_game.window);
    SDL_Quit();
    return 0;

}

void initialize_SDL()
{
    if(!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO| SDL_INIT_GAMEPAD))
    {
        SDL_Log("Failled to initialize. Error:%s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    g_game.window = SDL_CreateWindow("game title", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!g_game.window)
    {
        SDL_Log("Failed to create window. Error: %s", SDL_GetError());
    }
    g_game.renderer = SDL_CreateRenderer(g_game.window, NULL);
    if(!g_game.window)
    {
        SDL_Log("Failed to create window. Error: %s", SDL_GetError());   
    }

}