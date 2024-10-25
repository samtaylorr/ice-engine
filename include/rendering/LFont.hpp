#include "rendering/LTexture.hpp"
#include <memory>

#ifndef LFONT_H_
#define LFONT_H_

class LFont : public LTexture
{
    private:
        std::unique_ptr<SDL_Point> transform = std::make_unique<SDL_Point>(SDL_Point {0,0});
    public:
        //Allocates memory
        LFont(std::shared_ptr<LWindow> window, Scene &subject, std::string textureText, TTF_Font* font, SDL_Color textColor);
        void SetTransform(SDL_Point transform);
        ~LFont();

        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, TTF_Font* font, SDL_Color textColor );

        void Update() override;

    private:
        std::string fontName;
};

#endif