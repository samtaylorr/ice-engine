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
Scene currentScene;

//Globally used font
TTF_Font* gFont = TTF_OpenFont( "fonts/easvhs.ttf", 14 );
//Rendered texture
LFont testText = LFont(window, currentScene, "predev", gFont, {0,0,0,0});

std::shared_ptr<AnimatedSprite2D> animSprite = std::make_unique<AnimatedSprite2D>(window, currentScene, "img/main_character_sprite.png", "img/main_character_sprite.json");
PlayerController player = PlayerController(currentScene, animSprite);

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    testText.SetTransform({5,0});
    return success;
}

void close()
{
    //Free global font
    TTF_CloseFont(gFont);
    delete window;
}

int main( int argc, char* args[] )
{
    currentScene.CreateMessage(SCENE_START);

    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
    }
    else
    {	
        //Main loop flag
        bool quit = false;
        //While application is running
        double t = 0.0;
        double dt = 1.0 / 60.0;
        
        while( !Input::HasInitiatedQuit() )
        {
            //Clear screen
            window->Clear();

            Input::ProcessInput();
            t += dt;

            //Update currentScene
            currentScene.CreateMessage(SCENE_UPDATE);

            //Update screen
            window->Render();
        }
    }

	//Free resources and close SDL
	close();

	return 0;
}