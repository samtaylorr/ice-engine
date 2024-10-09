#include <Sprite2D.hpp>
#include <Settings.hpp>
#include <Input.hpp>
#include <iostream>

// if mult > 0, multiply by origin.x*(i*mult.x)
// else, return origin.x
int Sprite2D::_mult(int x, int i, int multiplier) { return (multiplier<=0) ? x : i*multiplier; }

Sprite2D::Sprite2D(LWindow *window, Scene &subject, SDL_Rect &area, SDL_Rect &mult, int &frames, const std::string &fileName) : Component(subject)
{
    spriteSheet = new LTexture(window, subject, fileName);
    this->frames = frames;
    clips = Sprite2D::GenerateClips(this->frames, area, mult);
}

Sprite2D::Sprite2D(LWindow *window, Scene &subject, const std::string &fileName) : Component(subject)
{
    spriteSheet = new LTexture(window, subject, fileName);
    this->frames = 0;
    clips = new SDL_Rect{0,0,spriteSheet->getWidth(),spriteSheet->getHeight()};
}

Sprite2D::Sprite2D(Scene &subject, SpriteData* spriteData) : Component(subject)
{
    this->spriteSheet = spriteData->spriteSheet;
    this->frames = spriteData->frames;
    this->clips = spriteData->clips;
}

Sprite2D::~Sprite2D()
{
    delete clips;
    delete spriteSheet;
}

void Sprite2D::Start()
{}

void Sprite2D::Update()
{
    currentClip = &clips[frame];
    spriteSheet->render( ( Settings::SCREEN_WIDTH - currentClip->w ) / 2, ( Settings::SCREEN_HEIGHT - currentClip->h ) / 2, currentClip, degrees, NULL, flipType );
    if(currentDuration >= duration)
    {
        //Go to next frame
        ++frame;
        //Cycle animation
        if( frame >= frames )
        {
            frame = 0;
        }
        currentDuration = 0;
    }
    else { ++currentDuration; }
}