#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <stdbool.h>


#define WIN 1
#define GAME 0


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



void init();
void initSDL();
void initGame();
void loadMedia();
void shutdown();
void keyPress(SDL_Event e);
void moveCreeps();
void spawnLaser();
void moveAndDeleteLasers();


SDL_Texture* loadTexture( char *path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* gRedTexture;
SDL_Texture* gGreenTexture;
SDL_Texture* gYellowTexture;
SDL_Texture* gExtraTexture;
SDL_Texture* gPlayerTexture;
SDL_Texture* gLaserTexture;

typedef struct player
{
    int life;
    SDL_Texture* texture;
    SDL_Rect position;


}player;

player gPlayer;


typedef struct enenmy
{
    int life;
    SDL_Texture* texture;
    int shootFrequency;
    SDL_Rect position;
    
}enemy;


enemy gEnemyArr[32];

typedef struct lasers
{
    int size;
    SDL_Texture* texture;
    SDL_Rect position[32];
    
}lasers;

lasers gLasers = {.size = 0};

