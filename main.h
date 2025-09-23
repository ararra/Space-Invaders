#pragma once

#include <stdlib.h>

#include <SDL3/SDL.h>


#define SCREEN_WIDTH 680
#define SCREEN_HEIGHT 420

typedef struct game
{
    SDL_Renderer* renderer;
    SDL_Window* window;

    SDL_Texture* Background;
}game;
game g_game;

typedef struct enemy
{

}enemy;





void initialize_SDL();
