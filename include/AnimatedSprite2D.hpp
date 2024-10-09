#include <json.hpp>
using json = nlohmann::json;
#include <SDL2/SDL.h>
#include <Sprite2D.hpp>

#ifndef ASE_SPRITE_2D_
#define ASE_SPRITE_2D_

class AnimatedSprite2D : public Component
{
private:
    SpriteData* spriteData;
    int frameStart = 0, frameEnd;
    int frame = frameStart, duration = 10, currentDuration = 0;
    SDL_Rect* currentClip;
    Animation* currentAnimation;
    void AddFrames(json &frame, std::vector<SDL_Rect>* v);
    SpriteData* GenerateSpriteData(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath);
    void Update() override;

public:
    AnimatedSprite2D(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath);
    void Play(Animation *animation);
    ~AnimatedSprite2D();
};

#endif