#include <Sprite2D.h>
#include <Settings.h>
#include <Input.h>
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
    this->frames = 4;
    clips = Sprite2D::GenerateClips(4, {0,0,64,205}, {64,0,0,0});
}

Sprite2D::~Sprite2D()
{
    delete clips;
    delete spriteSheet;
}

void Sprite2D::Start()
{
}

void Sprite2D::Update()
{
    if(Input::GetKeyDown(SDLK_a))
    {
        degrees += 60;
    }
    else if(Input::GetKeyDown(SDLK_d))
    {
        degrees -= 60;
    }
    else if(Input::GetKeyDown(SDLK_q))
    {
        flipType = SDL_FLIP_HORIZONTAL;
    }
    else if(Input::GetKeyDown(SDLK_w))
    {
        flipType = SDL_FLIP_NONE;
    }
    else if(Input::GetKeyDown(SDLK_e))
    {
        flipType = SDL_FLIP_VERTICAL;
    }

    currentClip = &clips[ frame / frames ];

    spriteSheet->render( ( Settings::SCREEN_WIDTH - currentClip->w ) / 2, ( Settings::SCREEN_HEIGHT - currentClip->h ) / 2, currentClip, degrees, NULL, flipType );

    //Go to next frame
    ++frame;

    //Cycle animation
    if( frame / 4 >= frames )
    {
        frame = 0;
    }
}