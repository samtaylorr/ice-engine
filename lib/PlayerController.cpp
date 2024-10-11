#include "PlayerController.hpp"
#include <iostream>
#include <Input.hpp>
#include "Settings.hpp"

void PlayerController::Update()
{
    moving = (Input::GetKeyDown(SDLK_a) || Input::GetKeyDown(SDLK_d));

    if(moving && !movingAnim)
    {
        if(vDirection == FACE_BACK){ sprite->SetAnim(*backWalk);  }
        else                      { sprite->SetAnim(*frontWalk); }
        movingAnim = true;
    }

    if(Input::GetKeyDown(SDLK_s) && !movingAnim)
    {
        sprite->SetAnim(*frontWalk);
        vDirection = FACE_FRONT;
        movingAnim = true;
    }
    
    if(Input::GetKeyDown(SDLK_w) && !movingAnim)
    {
        sprite->SetAnim(*backWalk);
        vDirection = FACE_BACK;
        movingAnim = true;
    }

    if(!Input::GetKeyDown(SDLK_s) && 
       !Input::GetKeyDown(SDLK_w) && 
       !Input::GetKeyDown(SDLK_a) && 
       !Input::GetKeyDown(SDLK_d) && movingAnim != false)
    {
        if(vDirection == FACE_BACK){ sprite->SetAnim(*backIdle);  }
        else                      { sprite->SetAnim(*frontIdle); }
        movingAnim = false;
    }

    sprite->SetDirection(isFaceLeft);

    Move();
    
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
    this->sprite = sprite;
    this->frontIdle = std::make_unique<Animation>(2,2, 10);        // Set the idle frames and duration
    this->frontWalk = std::make_unique<Animation>(0,2, 10);        // Set the walk frames and duration
    this->backIdle =  std::make_unique<Animation>(3,3, 10);        // Set the idle frames and duration for the back
    this->backWalk =  std::make_unique<Animation>(4,6, 10);        // Set the walk frames and duration for the back

    this->position = std::make_unique<SDL_Point>(SDL_Point{0,0});  // Set the position
}

PlayerController::~PlayerController()
{
}