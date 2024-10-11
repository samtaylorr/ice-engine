#include <SDL2/SDL.h>
#include <map>
#include <iostream>
#include <algorithm>

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
    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0 )
    {
        switch(e.type)
        {
            case SDL_KEYDOWN:
                keyboard[e.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                keyboard[e.key.keysym.sym] = false;
                break;
        }

        //User requests quit
        if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE )
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