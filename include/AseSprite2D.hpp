#include <json.hpp>
using json = nlohmann::json;
#include <SDL2/SDL.h>
#include <Sprite2D.hpp>

#ifndef ASE_SPRITE_2D_
#define ASE_SPRITE_2D_

class AseSprite2D : public Sprite2D
{
private:
    LTexture* spriteSheet;
    SDL_Rect* clips;
    int frames = 0;
    SpriteData* GenerateSpriteData(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath);
public:
    AseSprite2D(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath);
    ~AseSprite2D();
};

#endif