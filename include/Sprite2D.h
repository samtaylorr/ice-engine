#include "Component.h"
#include "LTexture.h"

#ifndef SPRITE_2D_H_
#define SPRITE_2D_H_

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
    
public:
    Sprite2D(LWindow* window, Scene &subject, const std::string& fileName);
    ~Sprite2D();
    void Start() override;
    void Update() override;

    static SDL_Rect* GenerateClips(int frames, SDL_Rect origin, SDL_Rect mask, SDL_Rect mult)   
    {
        SDL_Rect clips[frames];

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