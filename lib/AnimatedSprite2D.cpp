#include "AnimatedSprite2D.hpp"
#include <fstream>
#include <iostream>

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

AnimatedSprite2D::AnimatedSprite2D(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath) : 
Sprite2D(subject, GenerateSpriteData(window, subject, filePath, jsonPath)){}

AnimatedSprite2D::~AnimatedSprite2D()
{
}