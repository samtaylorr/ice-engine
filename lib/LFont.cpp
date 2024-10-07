#include "LFont.h"

LFont::LFont(LWindow *window, Scene &subject, std::string textureText, TTF_Font* font, SDL_Color textColor) : LTexture(window, subject)
{
    //Initialize
    mTexture = NULL;
    mRenderer = window->GetRenderer();
    mWidth = 0;
    mHeight = 0;
    this->fontName = fontName;
    this->loadFromRenderedText(textureText, font, textColor);
}

LFont::~LFont()
{
    free();
}

bool LFont::loadFromRenderedText( std::string textureText, TTF_Font* font, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( mRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return mTexture != NULL;
}

void LFont::Update()
{
    render(0,0);
}