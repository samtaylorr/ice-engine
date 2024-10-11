#include "AnimatedSprite2D.hpp"
#include <fstream>
#include <iostream>
#include <Settings.hpp>

void AnimatedSprite2D::AddFrames(json &frame, std::vector<SDL_Rect>* v)
{
    v->push_back({
        frame.at("frame").at("x"),
        frame.at("frame").at("y"),
        frame.at("frame").at("w"),
        frame.at("frame").at("h")
    });
}

SpriteData *AnimatedSprite2D::GenerateSpriteData(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath)
{
    SpriteData* spriteData = new SpriteData;
    std::ifstream f(jsonPath);
    json data = json::parse(f);
    std::vector<SDL_Rect>* framesVector = new std::vector<SDL_Rect>;
    int frameCount = 0;

    for(json frame : data.at("frames"))
    {
        this->AddFrames(frame, framesVector);
        frameCount++;
    }

    spriteData->spriteSheet = new LTexture(window, subject, filePath);
    spriteData->frames = frameCount;
    spriteData->clips = new SDL_Rect[frameCount];
    std::copy(framesVector->begin(), framesVector->end(), spriteData->clips);

    return spriteData;
}

void AnimatedSprite2D::Update()
{
    currentClip = &spriteData->clips[frame];
    //spriteData->spriteSheet->render( ( Settings::SCREEN_WIDTH - currentClip->w ) / 2, ( Settings::SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
    spriteData->spriteSheet->render( position->x, position->y, currentClip, 0.0, NULL, flipType );
    if(currentDuration >= duration)
    {
        //Go to next frame
        ++frame;
        //Cycle animation
        if( frame >= frameEnd )
        {
            frame = frameStart;
        }
        currentDuration = 0;
    }
    else { ++currentDuration; }
}

AnimatedSprite2D::AnimatedSprite2D(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath) : Component(subject)
{
    spriteData = GenerateSpriteData(window, subject, filePath, jsonPath);
    frameEnd = spriteData->frames;
    this->position = std::make_unique<SDL_Point>(SDL_Point{0,0});
}

AnimatedSprite2D::AnimatedSprite2D(Scene &subject) : Component(subject){}

void AnimatedSprite2D::SetAnim(Animation anim)
{
    frame = anim.frameStart;
    frameStart = anim.frameStart;
    frameEnd = anim.frameEnd;
    duration = anim.duration;
}

void AnimatedSprite2D::SetPosition(int x, int y)
{
    this->position->x = x;
    this->position->y = y;
}

void AnimatedSprite2D::SetDirection(bool faceLeft)
{
    if(faceLeft){ flipType = SDL_FLIP_HORIZONTAL; }
    else        { flipType = SDL_FLIP_NONE;       }
}

SDL_Rect* AnimatedSprite2D::GetCurrentFrame()
{
    return currentClip;
}
