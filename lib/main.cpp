//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//Our ICE library
#include <ice/ice.h>

// Define settings for compiler
const int Settings::SCREEN_WIDTH = 640;
const int Settings::SCREEN_HEIGHT = 480;

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

LWindow* window = new LWindow(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT);

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

Sprite2D* gSpriteSheetTexture = NULL;

//Globally used font
TTF_Font* gFont = TTF_OpenFont( "fonts/easvhs.ttf", 28 );

//Rendered texture
LFont* gTextTexture = NULL;

Scene* currentScene;

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    gTextTexture = new LFont(window, *currentScene, "test", gFont, {0,0,0,0});
    gSpriteSheetTexture = new Sprite2D(window, *currentScene, "img/foo.png");
    return success;
}


void close()
{
    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;
    delete window;
    delete gTextTexture;
    delete gSpriteSheetTexture;
}

int main( int argc, char* args[] )
{
    currentScene = new Scene();
    currentScene->CreateMessage(SCENE_START);

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

        //Update screen
        window->Render();
        
        //While application is running
        while( !Input::HasInitiatedQuit() )
        {
            //Clear screen
            window->Clear();

            Input::ProcessInput();

            //Update currentScene
            currentScene->CreateMessage(SCENE_UPDATE);
            
            //Render text
            gTextTexture->render(0,0);

            //Update screen
            window->Render();
            Input::Clear();
        }
    }

	//Free resources and close SDL
	close();

	return 0;
}