#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include "Component.hpp"
#include "Animation.hpp"
#include "AnimatedSprite2D.hpp"
#include <memory>

enum V_DIRECTIONS
{
    FACE_FRONT,
    FACE_BACK,
    IDLE
};

class PlayerController : public Component
{
private:
    int mPosX, mPosY, mVelX, mVelY;
    std::unique_ptr<Animation> frontIdle, frontWalk, backIdle, backWalk;
    std::shared_ptr<AnimatedSprite2D> sprite;
    std::unique_ptr<SDL_Point> position;
    V_DIRECTIONS vDirection;
    bool moving = false, movingAnim = false, isFaceLeft = false;
    void Update() override;
public:
    //Maximum axis velocity of the dot
    static const int VELOCITY = 10;
    PlayerController(Scene &subject, std::shared_ptr<AnimatedSprite2D> sprite);
    ~PlayerController();
    void Move();
};

#endif