#include "main.h"

void init()
{
    initSDL();
    initGame();
}

void initSDL()
{

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
    }
    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
    }
    gRenderer = SDL_CreateRenderer( gWindow,-1, SDL_RENDERER_ACCELERATED);
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
    }
    int imgFlags = IMG_INIT_JPG;
    if(IMG_Init(imgFlags) != imgFlags )
    {
        printf("Failed to load image library");
        exit(EXIT_FAILURE);
    }

}

void initGame()
{
    gRedTexture = loadTexture("assets/red.png");
    gExtraTexture = loadTexture("assets/extra.png");
    gYellowTexture = loadTexture("assets/yellow.png");
    gGreenTexture = loadTexture("assets/green.png");
    gLaserTexture = loadTexture("assets/01.png");

    gPlayer.texture = loadTexture("assets/player.png");

    for(int i= 0; i < sizeof(gEnemyArr)/sizeof(gEnemyArr[0]); i++)
    {
        if(i < 16)
        {
            gEnemyArr[i].texture = gRedTexture;
            gEnemyArr[i].position.y = 40;
            if (i >7)
            {
                gEnemyArr[i].position.y = 100;

            }
        }
        else if(i < 24 & i > 15)
        {
            gEnemyArr[i].texture = gYellowTexture;
            gEnemyArr[i].position.y = 160;
        }
        else
        {
            gEnemyArr[i].texture = gGreenTexture;
            gEnemyArr[i].position.y = 220;
        }

        gEnemyArr[i].position.x = 64+i*SCREEN_WIDTH/10 % (SCREEN_WIDTH/10*8);

        // they should be the same but they arent
        // SDL_Log("lol %d vs %d",(i+1)*SCREEN_WIDTH/10, 64+i*SCREEN_WIDTH/10);
        gEnemyArr[i].position.w = 40;
        gEnemyArr[i].position.h = 32;
    }

    gPlayer.position.x = SCREEN_WIDTH/2-32;
    gPlayer.position.y = SCREEN_HEIGHT-84;
    gPlayer.position.w = 60;
    gPlayer.position.h = 30;
    }

void shutdown()
{
    //Deallocate Textures
    SDL_DestroyTexture(gRedTexture);
    SDL_DestroyTexture(gYellowTexture);
    SDL_DestroyTexture(gPlayer.texture);
    SDL_DestroyTexture(gGreenTexture);
    SDL_DestroyTexture(gExtraTexture);

    gRedTexture = NULL;
    gExtraTexture = NULL;
    gYellowTexture = NULL;
    gGreenTexture = NULL;
    gPlayer.texture = NULL;


    //Destroy window and renderer
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( char *path )
{
    //Load image at specified path
    SDL_Texture * loadedTexture = IMG_LoadTexture(gRenderer, path);
    if( loadedTexture == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path, IMG_GetError() );
    }

    return loadedTexture;
}

void moveCreeps()// this is wrong come back to it with clear head
{   bool left = false;
    if (SDL_GetTicks64() % 1000 == 0)
    {   
        if (SCREEN_WIDTH - gEnemyArr[7].position.x > 20)
        {
            for (int i = 0; i < sizeof(gEnemyArr)/sizeof(gEnemyArr[0]); i++)
            {   
                // printf("%d", SCREEN_WIDTH - gEnemyArr[7].position.x);
                gEnemyArr[i].position.x++;
            }    
        }
        else if(gEnemyArr[0].position.x > 20)
        {
            for (int i = 0; i < sizeof(gEnemyArr)/sizeof(gEnemyArr[0]); i++)
            {
                gEnemyArr[i].position.x--;
            }    
        }
        
    }
    
}

void spawnLaser()
{
    
    gLasers.position[gLasers.size].x = gPlayer.position.x - 30;
    gLasers.position[gLasers.size].y = gPlayer.position.y - 80;
    gLasers.position[gLasers.size].w = 120;
    gLasers.position[gLasers.size].h = 120;
    gLasers.texture = gLaserTexture;

    gLasers.size++;

}


void keyPress(SDL_Event e)
{
    switch (e.key.keysym.sym )
    {
    case SDLK_LEFT:
        gPlayer.position.x -= 8;
        break;
    case SDLK_RIGHT:
        gPlayer.position.x += 8;
        break;    
    case SDLK_SPACE:
        spawnLaser();
        break;
    
    default:
        break;
    }
}
void moveAndDeleteLasers()
{
    if (SDL_GetTicks64() % 1000 == 0)
    {
        for(int i; i < gLasers.size; i++)
        {
            gLasers.position[i].y-=10;
            if (gLasers.position[i].y==0)
            {
                //remove laser from array shift others down...or just change to linked list.
            }
            
        }
        
    }

}



int main()
{
    //Start up SDL and create window
    init();


    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {                
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            //User presses a key
            if( e.type == SDL_KEYDOWN )
            {
                keyPress(e);
            }
        }

        moveCreeps();
        moveAndDeleteLasers();

        //Clear screen
        SDL_RenderClear( gRenderer );


        for(int i= 0; i <  sizeof(gEnemyArr)/sizeof(gEnemyArr[0]); i++)
        {
            SDL_RenderCopy(gRenderer, gEnemyArr[i].texture, NULL, &gEnemyArr[i].position);
        }
        for(int i= 0; i <  gLasers.size; i++)
        {
            SDL_RenderCopy(gRenderer, gLasers.texture, NULL, &gLasers.position[i]);
        }
        
        SDL_RenderCopy(gRenderer, gPlayer.texture, NULL, &gPlayer.position);

        SDL_RenderPresent( gRenderer );
    
    }
    

    //Free resources and close SDL
    shutdown();

    return 0;
}