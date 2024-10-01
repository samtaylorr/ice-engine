//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//Our ICE library
#include <ice/ice.h>>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;

//Globally used font
TTF_Font* gFont = NULL;

//Rendered texture
LTexture gTextTexture;

int Scene::static_number_ = 0;

Scene *scene;
Component *component1;
Component *component2;
Component *component3;

void ClientCode() {
   scene = new Scene;
   component1 = new Component(*scene);
   component2 = new Component(*scene);
   component3 = new Component(*scene);

   scene->CreateMessage(SCENE_START);
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Set renderer on sprite sheet
    gSpriteSheetTexture.setRenderer(gRenderer);

    //Set renderer on text
    gTextTexture.setRenderer(gRenderer);

    //Load sprite sheet texture
    if( !gSpriteSheetTexture.loadFromFile( "img/foo.png" ) )
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else
    {
        //Set sprite clips
        // Rect that selects the first sprite in the animation
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w =  64;
        gSpriteClips[ 0 ].h = 205;

        // Rect that selects the second sprite in the animation
        gSpriteClips[ 1 ].x =  64;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w =  64;
        gSpriteClips[ 1 ].h = 205;
        
        // Rect that selects the third sprite in the animation
        gSpriteClips[ 2 ].x = 128;
        gSpriteClips[ 2 ].y =   0;
        gSpriteClips[ 2 ].w =  64;
        gSpriteClips[ 2 ].h = 205;

        // Rect that selects the fourth sprite in the animation
        gSpriteClips[ 3 ].x = 192;
        gSpriteClips[ 3 ].y =   0;
        gSpriteClips[ 3 ].w =  64;
        gSpriteClips[ 3 ].h = 205;
    }

    //Open the font
    gFont = TTF_OpenFont( "fonts/easvhs.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        if( !gTextTexture.loadFromRenderedText( "The quick brown fox jumps over the lazy dog", gFont, textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
    
    return success;
}


void close()
{
    //Free loaded images
    gSpriteSheetTexture.free();
    gTextTexture.free();

    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    delete component3;
    delete component2;
    delete component1;
    delete scene;

    //Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    ClientCode();
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}

	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Current animation frame
            int frame = 0;

            //Angle of rotation
            double degrees = 0;

            //Flip type
            SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL;

            //Update screen
            SDL_RenderPresent( gRenderer );
            
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
                    else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_a:
                            degrees += 60;
                            break;
                            
                            case SDLK_d:
                            degrees -= 60;
                            break;

                            case SDLK_q:
                            flipType = SDL_FLIP_HORIZONTAL;
                            break;

                            case SDLK_w:
                            flipType = SDL_FLIP_NONE;
                            break;

                            case SDLK_e:
                            flipType = SDL_FLIP_VERTICAL;
                            break;
                        }
                    }
                }

                //Update Scene
                scene->CreateMessage(SCENE_UPDATE);

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render current frame
                SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
                gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip, degrees, NULL, flipType );
                
                //Render text
                gTextTexture.render(0,0);

                //Update screen
                SDL_RenderPresent( gRenderer );

                //Go to next frame
                ++frame;

                //Cycle animation
                if( frame / 4 >= WALKING_ANIMATION_FRAMES )
                {
                    frame = 0;
                }
            }
        }
    }

	//Free resources and close SDL
	close();

	return 0;
}