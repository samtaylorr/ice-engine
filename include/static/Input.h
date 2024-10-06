#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>

#ifndef _INPUT_H_
#define _INPUT_H_

class Input
{
private:
    static std::vector<int> keys_down, keys;
    static bool quit;
public:
    static void ProcessInput();
    static bool GetKeyDown(SDL_Keycode key);
    static bool GetKey(SDL_Keycode key);
    static void Clear();
    static bool HasInitiatedQuit();
};

inline void Input::ProcessInput()
{
    SDL_Event e;
    Input::Clear();

    while( SDL_PollEvent( &e ) != 0 )
    {
        if (e.type == SDL_KEYDOWN)
        {
            Input::keys_down.push_back(e.key.keysym.sym);
        }
        else
        {
            Input::keys.push_back(e.key.keysym.sym);
        }
        //User requests quit
        if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE )
        {
            quit = true;
        }
    }
}

inline bool Input::GetKey(SDL_Keycode key)
{
    if(std::find(Input::keys.begin(), Input::keys.end(), key)!=Input::keys.end()){
      return key;
    }
    
    return false;
}

inline bool Input::GetKeyDown(SDL_Keycode key)
{
    if(std::find(Input::keys_down.begin(), Input::keys_down.end(), key)!=Input::keys_down.end()){
      return key;
    }
    
    return false;
}

inline void Input::Clear()
{
    Input::keys_down.clear();
    Input::keys.clear();
}

inline bool Input::HasInitiatedQuit()
{
    return quit;
}

#endif