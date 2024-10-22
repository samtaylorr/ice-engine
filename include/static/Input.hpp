#include <SDL2/SDL.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <memory>

#ifndef _INPUT_H_
#define _INPUT_H_

class Input
{
private:
    static std::map<int, bool> keyboard;
    static bool quit;
public:
    static void ProcessInput();
    static bool GetKeyDown(SDL_Keycode key);
    static bool HasInitiatedQuit();
};

inline void Input::ProcessInput()
{
    // This leaks memory, I don't know, 
    // I blame SDL2 since I'm using SDL_PollEvent() 
    // the way they reccomend in their documentation
    // bleh.
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 )
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                keyboard[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                keyboard[event.key.keysym.sym] = false;
                break;
        }

        //User requests quit
        if( event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE )
        {
            quit = true;
        }
    }
}

inline bool Input::GetKeyDown(SDL_Keycode key)
{
    return keyboard[key];
    
}

inline bool Input::HasInitiatedQuit()
{
    return quit;
}

#endif