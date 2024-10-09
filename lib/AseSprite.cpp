#include "AseSprite2D.hpp"
#include <fstream>
#include <iostream>

SpriteData* AseSprite2D::GenerateSpriteData(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath)
{
    SpriteData* spriteData = new SpriteData;

    std::ifstream f(jsonPath);
    json data = json::parse(f);

    std::vector<SDL_Rect> framesVector;
    int frameCount = 0;

    std::cout << "made";

    for(json frame : data.at("frames"))
    {
        framesVector.push_back({
            frame.at("frame").at("x"),
            frame.at("frame").at("y"),
            frame.at("frame").at("w"),
            frame.at("frame").at("h")
        });
        frameCount++;
    }

    spriteData->spriteSheet = new LTexture(window, subject, filePath);
    spriteData->frames = frameCount;
    spriteData->clips = new SDL_Rect[frameCount];
    std::copy(framesVector.begin(), framesVector.end(), spriteData->clips);

    return spriteData;
}

AseSprite2D::AseSprite2D(LWindow *window, Scene &subject, const std::string &filePath, const std::string &jsonPath) : 
Sprite2D(subject, GenerateSpriteData(window, subject, filePath, jsonPath))
{}

AseSprite2D::~AseSprite2D()
{
}