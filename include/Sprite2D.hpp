#include "Component.hpp"
#include "LTexture.hpp"

#ifndef SPRITE_2D_H_
#define SPRITE_2D_H_

struct SpriteData
{
    public:
        LTexture* spriteSheet;
        SDL_Rect* clips;
        int frames = 0;
};

class Sprite2D : public Component
{
private:
    LTexture* spriteSheet;
    SDL_Rect* clips;
    int frames = 0;
    //Current animation frame
    int frame = 0;
    //Angle of rotation
    double degrees = 0;
    //Flip type
    SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL;
    //Current clip
    SDL_Rect* currentClip;
    static int _mult(int x, int i, int multiplier);
    int duration = 5, currentDuration = 0;
    
public:
    Sprite2D(LWindow* window, Scene &subject, SDL_Rect &area, SDL_Rect &mult, int &frames, const std::string& fileName);
    Sprite2D(LWindow* window, Scene &subject, const std::string& fileName);
    Sprite2D(Scene &subject, SpriteData* spriteData);
    ~Sprite2D();
    void Start() override;
    void Update() override;

    static SDL_Rect* GenerateClips(int frames, SDL_Rect origin, SDL_Rect mult)   
    {
        SDL_Rect* clips = new SDL_Rect[frames];

        for(int i=0; i<frames; i++)
        {
            clips[i] = {
                _mult(origin.x, i, mult.x),
                _mult(origin.y, i, mult.y),
                _mult(origin.w, i, mult.w),
                _mult(origin.h, i, mult.h)
            };
        }

        return clips;
    };
};

#endif