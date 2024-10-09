//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//Our ICE library
#include <ice/ice.hpp>

// Define settings for compiler
const int Settings::SCREEN_WIDTH = 1280;
const int Settings::SCREEN_HEIGHT = 720;

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

LWindow* window = new LWindow(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT);

//Walking animation
AnimatedSprite2D* player = NULL;

//Globally used font
TTF_Font* gFont = TTF_OpenFont( "fonts/easvhs.ttf", 14 );

//Rendered texture
LFont* testText = NULL;

Scene* currentScene;

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    testText = new LFont(window, *currentScene, "predev", gFont, {0,0,0,0});
    testText->SetTransform({5,0});
    player = new AnimatedSprite2D(window, *currentScene, "img/main_character_sprite.png", "img/main_character_sprite.json");
    return success;
}

void close()
{
    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;
    delete window;
    delete testText;
    delete player;
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

            //Update screen
            window->Render();
            Input::Clear();
        }
    }

	//Free resources and close SDL
	close();

	return 0;
}