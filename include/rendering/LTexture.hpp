#include <string>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include "core/Component.hpp"
#include "rendering/LWindow.hpp"

#include <memory>

#ifndef LTEXTURE_H_
#define LTEXTURE_H_

//Texture wrapper class
class LTexture : public Component
{
    public:
        //Allocates memory
        LTexture(std::shared_ptr<LWindow> window, Scene &subject, const std::string& fileName);
        LTexture(std::shared_ptr<LWindow> window, Scene &subject);

        //Deallocates memory
        ~LTexture();

        void setRenderer(SDL_Renderer* renderer);

        //Loads image at specified path
        bool loadFromFile( std::string path );

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip );

        //Renders to screen
        void render( int x, int y );
        
        //Renders to screen with clips
        void render( int x, int y, SDL_Rect* clip );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Gets image dimensions
        int getWidth();
        int getHeight();

        //The actual hardware texture
        SDL_Texture* mTexture;

        //The renderer
        SDL_Renderer* mRenderer;

        //Image dimensions
        int mWidth;
        int mHeight;
        std::string fileName;
};

#endif