#pragma once

#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640   

typedef struct game
{
    SDL_Renderer* renderer;
    SDL_Window* window;

    SDL_Texture* Background;
    SDL_Texture* player_texture;
    SDL_Texture* bullet_texture;
}game;
game g_game;

typedef struct enemy_red
{
    SDL_Texture* texture;
    int health_arr[10];
}enemy_red;

enemy_red g_enemy_red;

typedef struct enemy_green
{
    SDL_Texture* texture;
    int health_arr[10];
}enemy_green;
enemy_green g_enemy_green;


typedef struct enemy_yellow
{
    SDL_Texture* texture;
    int health_arr[10];
}enemy_yellow;

enemy_yellow g_enemy_yellow;


void initialize_SDL();
void load_in_textures();