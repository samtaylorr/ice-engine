#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>

#ifndef _INPUT_H_
#define _INPUT_H_

class Input
{
private:
    static std::vector<int> keys_pressed;
public:
    static void ProcessInput();
    static bool GetKeyDown(SDL_Keycode key);
    static void Clear();
};

inline void Input::ProcessInput()
{
    SDL_Event e;
    Input::Clear();

    while( SDL_PollEvent( &e ) != 0 )
    {
        Input::keys_pressed.push_back(e.key.keysym.sym);
    }
}

inline bool Input::GetKeyDown(SDL_Keycode key)
{
    if(std::find(Input::keys_pressed.begin(), Input::keys_pressed.end(), key)!=Input::keys_pressed.end()){
      return key;
    }
    
    return false;
}

inline void Input::Clear()
{
    Input::keys_pressed.clear();
}

#endif