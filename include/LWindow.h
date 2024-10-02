#ifndef L_PROGRAM_L
#define L_PROGRAM_L

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class LWindow
{
public:
    LWindow(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT);
    ~LWindow();
    SDL_Window* GetWindow();
    SDL_Renderer* GetRenderer();
    void Render();
    bool IsInit();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool LoadSDLExtensions();
    bool Init();
    int _height = NULL;
    int _width = NULL;
    bool _isInit = false;
};

#endif