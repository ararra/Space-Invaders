#pragma once

#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 700   
#define ENEMY_SIZE_MAX 10
#define BULLET_RENDER_MAX 10



typedef struct game
{
    SDL_Renderer* renderer;
    SDL_Window* window;

    SDL_Texture* Background;
    SDL_Texture* player_texture;
    SDL_Texture* bullet_texture;
    SDL_FRect player_position;
    SDL_FRect bullet_position_arr[BULLET_RENDER_MAX];

}game;
game g_game;

typedef struct enemy_red
{
    SDL_Texture* texture;
    int health_arr[ENEMY_SIZE_MAX];
    SDL_FRect position_arr[ENEMY_SIZE_MAX]
}enemy_red;

typedef struct enemy_green
{
    SDL_Texture* texture;
    int health_arr[ENEMY_SIZE_MAX];
    SDL_FRect position_arr[ENEMY_SIZE_MAX]
}enemy_green;


typedef struct enemy_yellow
{
    SDL_Texture* texture;
    int health_arr[ENEMY_SIZE_MAX];
    SDL_FRect position_arr[ENEMY_SIZE_MAX]
}enemy_yellow;



//Global variables
game g_game;
enemy_red g_enemy_red;
enemy_green g_enemy_green;
enemy_yellow g_enemy_yellow;



//function prototypes
void initialize_game();
void initialize_SDL();
void load_in_textures();
void set_start_variables();
void handle_player_movement(uint64_t time_delta);
void enemy_move();