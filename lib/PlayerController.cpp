#include "PlayerController.hpp"
#include <iostream>
#include <Input.hpp>
#include "Settings.hpp"

void PlayerController::Update()
{
    std::unique_ptr<SDL_Point> lastPosition = std::make_unique<SDL_Point>(*position);
    Move();
    // this is the worst code i've ever written in my life
    if      (lastPosition->y < position->y) { *currentAnimation=*frontWalk;                     }
    else if (lastPosition->y > position->y) { *currentAnimation=*backWalk;                      }
    else if (lastPosition->x > position->x ){ *currentAnimation=*sideWalk; isFaceLeft = true;   }
    else if (lastPosition->x < position->x) { *currentAnimation=*sideWalk; isFaceLeft = false;  }
    else if (lastPosition->x == position->x && lastPosition->y == position->y)
    {
        if     (currentAnimation->name=="Front_Walk")  { *currentAnimation=*frontIdle;}
        else if(currentAnimation->name=="Back_Walk")   { *currentAnimation=*backIdle; }
        else if(currentAnimation->name=="Side_Walk")   { *currentAnimation=*sideIdle; }
    }

    sprite->SetDirection(isFaceLeft);
    sprite->SetAnim(*currentAnimation);
    
    return;
}

void PlayerController::Move()
{
    if(Input::GetKeyDown(SDLK_w))           // W
    {
        position->y -= VELOCITY;
    }
    if(Input::GetKeyDown(SDLK_s))           // S
    {
        position->y += VELOCITY;
    }
    if(Input::GetKeyDown(SDLK_a))           // A
    {
        position->x -= VELOCITY;
    }
    if(Input::GetKeyDown(SDLK_d))           // D
    {
        position->x += VELOCITY;
    }

    sprite->SetPosition(
        position->x,
        position->y
    );
}

PlayerController::PlayerController(Scene &subject, std::shared_ptr<AnimatedSprite2D> sprite) : Component(subject)
{
    //nvm i changed my mind, THIS is the worst code I've ever written
    this->sprite = sprite;
    this->frontIdle = std::make_unique<Animation>("Front_Idle", 2,2, 10);        // Set the idle frames and duration
    this->frontWalk = std::make_unique<Animation>("Front_Walk", 0,2, 10);        // Set the walk frames and duration
    this->backIdle =  std::make_unique<Animation>("Back_Idle", 3,3, 10);        // Set the idle frames and duration for the back
    this->backWalk =  std::make_unique<Animation>("Back_Walk", 4,6, 10);        // Set the walk frames and duration for the back
    this->sideWalk =  std::make_unique<Animation>("Side_Walk", 6,8, 10);        // Set the walk frames and duration for the side
    this->sideIdle =  std::make_unique<Animation>("Side_Idle", 7,7, 10);        // Set the idle frames and duration for the side
    this->position = std::make_unique<SDL_Point>(SDL_Point{0,0});  // Set the position
    this->currentAnimation = std::make_unique<Animation>(*frontIdle);
}

PlayerController::~PlayerController()
{
}
