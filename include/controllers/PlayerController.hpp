#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_

#include "core/Component.hpp"
#include "sprite/Animation.hpp"
#include "sprite/AnimatedSprite2D.hpp"
#include <memory>

enum V_DIRECTIONS
{
    FACE_FRONT,
    FACE_BACK,
    SIDE_LEFT,
    SIDE_RIGHT,
    IDLE
};

class PlayerController : public Component
{
private:
    int mPosX, mPosY, mVelX, mVelY;
    std::unique_ptr<Animation> frontIdle, frontWalk, backIdle, backWalk, sideWalk, sideIdle, currentAnimation;
    std::shared_ptr<AnimatedSprite2D> sprite;
    std::unique_ptr<SDL_Point> position;
    V_DIRECTIONS vDirection;
    bool moving = false, movingAnim = false, isFaceLeft = false;
    void Update() override;
public:
    //Maximum axis velocity of the dot
    static const int VELOCITY = 3;
    PlayerController(Scene &subject, std::shared_ptr<AnimatedSprite2D> sprite);
    ~PlayerController();
    void Move();
};

#endif