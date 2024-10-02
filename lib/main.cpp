//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//Our ICE library
#include <ice/ice.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

LWindow* window = new LWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

int Scene::static_number_ = 0;

Scene scene;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

LTexture* gSpriteSheetTexture = NULL;

//Globally used font
TTF_Font* gFont = TTF_OpenFont( "fonts/easvhs.ttf", 28 );

//Rendered texture
LFont* gTextTexture = NULL;

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    gTextTexture = new LFont(window, scene, "test", gFont, {0,0,0,0});
    gSpriteSheetTexture = new LTexture(window, scene, "img/foo.png");
    //Load sprite sheet texture
    for(int i=0; i<WALKING_ANIMATION_FRAMES; i++)
    {
        gSpriteClips[i] = {64*i, 0, 64, 205};
    }
    
    return success;
}


void close()
{
    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

    delete window;
}

int main( int argc, char* args[] )
{
    scene = Scene();
    scene.CreateMessage(SCENE_START);

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
        window->Render();
        
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

                        case SDLK_ESCAPE:
                        quit = true;
                        break;
                    }
                }
            }

            //Update Scene
            scene.CreateMessage(SCENE_UPDATE);

            //Clear screen
            SDL_SetRenderDrawColor( window->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( window->GetRenderer() );

            //Render current frame
            SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];
            gSpriteSheetTexture->render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip, degrees, NULL, flipType );
            
            //Render text
            gTextTexture->render(0,0);

            //Update screen
            SDL_RenderPresent( window->GetRenderer() );

            //Go to next frame
            ++frame;

            //Cycle animation
            if( frame / 4 >= WALKING_ANIMATION_FRAMES )
            {
                frame = 0;
            }
        }
    }

	//Free resources and close SDL
	close();

	return 0;
}