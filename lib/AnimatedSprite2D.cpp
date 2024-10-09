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
    spriteData->spriteSheet->render( ( Settings::SCREEN_WIDTH - currentClip->w ) / 2, ( Settings::SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
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
}

void AnimatedSprite2D::Play(Animation *animation)
{
    this->currentAnimation = animation;
}

AnimatedSprite2D::~AnimatedSprite2D()
{
}