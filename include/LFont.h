#include "LTexture.h"

#ifndef LFONT_H_
#define LFONT_H_

class LFont : public LTexture
{
    public:
        //Allocates memory
        LFont(LWindow *window, Scene &subject, std::string textureText, TTF_Font* font, SDL_Color textColor);
        ~LFont();

        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, TTF_Font* font, SDL_Color textColor );

    private:
        std::string fontName;
};

#endif