#include "main.h"


int main()
{
    bool game_is_running = true;
    SDL_Event event;
    initialize_game();
    uint64_t last_time = 0, current_time;


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
        current_time = SDL_GetTicks();
        uint64_t time_delta = (current_time-last_time);
        SDL_Log("time delta is %d", time_delta);
        last_time = current_time;

        //continuous player movement
        handle_player_movement(time_delta);
        enemy_move();

        // Render


        SDL_RenderClear(g_game.renderer);


        ////
        // Set render color to white renders a filled white rectangle and sets the render color back in black
        ////
        // SDL_SetRenderDrawColor(g_game.renderer, 0b11111111, 0b11111111, 0b11111111, SDL_ALPHA_OPAQUE);
        // SDL_FRect box = {.x = 50, .y = 50 , .h = 50, .w = 50};
        // SDL_RenderFillRect(g_game.renderer, &box);
        // SDL_SetRenderDrawColor(g_game.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        //render assets 
        SDL_RenderTexture(g_game.renderer, g_game.player_texture, NULL, &g_game.player_position);

        for(int i = 0; i<ENEMY_SIZE_MAX; i++){
            SDL_RenderTexture(g_game.renderer, g_enemy_red.texture, NULL, &g_enemy_red.position_arr[i]);
            SDL_RenderTexture(g_game.renderer, g_enemy_yellow.texture, NULL, &g_enemy_yellow.position_arr[i]);
            SDL_RenderTexture(g_game.renderer, g_enemy_green.texture, NULL, &g_enemy_green.position_arr[i]);
        }




        SDL_SetRenderDrawColor(g_game.renderer, 32, 32, 32, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(g_game.renderer);


        SDL_Delay(16.7);


    }
    
    SDL_DestroyRenderer(g_game.renderer);
    SDL_DestroyWindow(g_game.window);
    SDL_Quit();
    return 0;

}


void handle_player_movement(uint64_t time_delta){
    const bool *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W])
    {
        g_game.player_position.y -= time_delta;
    }
    if (keys[SDL_SCANCODE_S])
    {
        g_game.player_position.y += time_delta;
    }
    if (keys[SDL_SCANCODE_A])
    {
        g_game.player_position.x -= time_delta;
    }
    if (keys[SDL_SCANCODE_D])
    {
        g_game.player_position.x += time_delta;
    }
    

}
void enemy_move()
{
    SDL_Log("%d",g_enemy_green.position_arr[0].y);
    if (g_enemy_green.position_arr[0].y <= SCREEN_HEIGHT-g_enemy_green.position_arr[0].h)
    {
        for(int i = 0; i < ENEMY_SIZE_MAX; i++)
        {
            g_enemy_red.position_arr[i].y += 5.0; 
            g_enemy_yellow.position_arr[i].y += 5.0;
            g_enemy_green.position_arr[i].y += 5.0;
        }   
    }
}

void initialize_game(){    
    initialize_SDL();
    load_in_textures();
    set_start_variables();
}

void initialize_SDL(){
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

void load_in_textures(){   
    SDL_Surface* temp = IMG_Load("assets/01.png");
    g_game.bullet_texture = SDL_CreateTextureFromSurface(g_game.renderer, temp);

    temp = IMG_Load("assets/player.png");
    g_game.player_texture = SDL_CreateTextureFromSurface(g_game.renderer, temp);

    temp = IMG_Load("assets/green.png");
    g_enemy_green.texture =  SDL_CreateTextureFromSurface(g_game.renderer, temp);

    temp = IMG_Load("assets/yellow.png");
    g_enemy_yellow.texture = SDL_CreateTextureFromSurface(g_game.renderer, temp);

    temp = IMG_Load("assets/red.png");
    g_enemy_red.texture = SDL_CreateTextureFromSurface(g_game.renderer, temp);

}

void set_start_variables(){

    g_game.player_position = (SDL_FRect){.x = 375, .y = 600 , .h = 50, .w = 50};

    for(int i = 0; i < ENEMY_SIZE_MAX; i++)
    {
        g_enemy_red.health_arr[i] = 3;
        g_enemy_red.position_arr[i] = (SDL_FRect){.x = 20 + i*70, .y = 20, .w = 50 , .h = 50};
        g_enemy_yellow.health_arr[i] = 2;
        g_enemy_yellow.position_arr[i] = (SDL_FRect){.x = 20 + i*70, .y = 120, .w = 50 , .h = 50};
        g_enemy_green.health_arr[i] = 1;
        g_enemy_green.position_arr[i] = (SDL_FRect){.x = 20 + i*70, .y = 220, .w = 50 , .h = 50};
        

    }
}
