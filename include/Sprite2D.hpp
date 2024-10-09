#include "Component.hpp"
#include "LTexture.hpp"
#include "Animation.hpp"

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
    LTexture* sprite;

public:
    Sprite2D(LWindow* window, Scene &subject, const std::string& fileName);
    ~Sprite2D();
};

#endif