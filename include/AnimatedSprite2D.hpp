#include <json.hpp>
using json = nlohmann::json;
#include <SDL2/SDL.h>
#include <Sprite2D.hpp>
#include <memory>

#ifndef ASE_SPRITE_2D_
#define ASE_SPRITE_2D_

class AnimatedSprite2D : public Component
{
private:
    SpriteData* spriteData;
    int frameStart = 0, frameEnd;
    int frame = frameStart, duration = 10, currentDuration = 0;
    SDL_Rect* currentClip;
    std::unique_ptr<SDL_Point> position;
    void AddFrames(json &frame, std::vector<SDL_Rect>* v);
    SpriteData* GenerateSpriteData(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath);
    void Update() override;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

public:
    AnimatedSprite2D(Scene &subject);
    AnimatedSprite2D(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath);
    void SetAnim(Animation anim), SetPosition(int x, int y), SetDirection(bool faceLeft);
    SDL_Rect* GetCurrentFrame();
};

#endif