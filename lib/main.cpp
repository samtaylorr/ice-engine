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

std::shared_ptr<LWindow> window = std::make_unique<LWindow>(Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT);
std::unique_ptr<Scene> currentScene = std::make_unique<Scene>();

//Globally used font
// Can't use RAII because of SDL being C-compatible (ew)
TTF_Font* gFont = TTF_OpenFont( "fonts/easvhs.ttf", 14 );
//Rendered texture
LFont testText = LFont(window, *currentScene, "predev", gFont, {0,0,0,0});

//                                                                                                       Spritesheet                      Spritesheet instructions
std::shared_ptr<AnimatedSprite2D> animSprite = std::make_unique<AnimatedSprite2D>(window, *currentScene, "img/main_character_sprite.png", "img/main_character_sprite.json");
std::unique_ptr<PlayerController> player     = std::make_unique<PlayerController>(*currentScene, animSprite);

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    
    return success;
}

void close()
{
    //Free global font
    TTF_CloseFont(gFont);
}

int main( int argc, char* args[] )
{
    currentScene->CreateMessage(SCENE_START);
    testText.SetTransform({5,0});

    while( !Input::HasInitiatedQuit() )
    {
        //Clear screen
        window->Clear();

        Input::ProcessInput();

        //Update currentScene
        currentScene->CreateMessage(SCENE_UPDATE);

        //Update screen
        window->Render();
    }

	//Free resources and close SDL
	close();

	return 0;
}