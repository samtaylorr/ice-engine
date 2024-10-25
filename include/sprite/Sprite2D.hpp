#include "core/Component.hpp"
#include "rendering/LTexture.hpp"
#include "sprite/Animation.hpp"

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
    Sprite2D(std::shared_ptr<LWindow> window, Scene &subject, const std::string& fileName);
    ~Sprite2D();
};

#endif