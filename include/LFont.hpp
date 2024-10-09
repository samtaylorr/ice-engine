#include "LTexture.hpp"

#ifndef LFONT_H_
#define LFONT_H_

class LFont : public LTexture
{
    private:
        SDL_Point transform = {0,0};
    public:
        //Allocates memory
        LFont(LWindow *window, Scene &subject, std::string textureText, TTF_Font* font, SDL_Color textColor);
        void SetTransform(SDL_Point transform);
        ~LFont();

        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, TTF_Font* font, SDL_Color textColor );

        void Update() override;

    private:
        std::string fontName;
};

#endif