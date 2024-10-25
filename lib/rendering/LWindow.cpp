#include <rendering/LWindow.hpp>

LWindow::LWindow(const int &SCREEN_WIDTH, const int &SCREEN_HEIGHT)
{
	this->_width = SCREEN_WIDTH;
	this->_height = SCREEN_HEIGHT;
	this->_isInit = this->Init();
}

LWindow::~LWindow()
{
    //Destroy window    
    SDL_DestroyRenderer( this->renderer );
    SDL_DestroyWindow( this->window );
    this->window = NULL;
    this->renderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

SDL_Window* LWindow::GetWindow()
{
    return this->window;
}

SDL_Renderer* LWindow::GetRenderer()
{
    return this->renderer;
}

void LWindow::Render()
{
	SDL_RenderPresent( this->renderer );
}

void LWindow::Clear()
{
	SDL_SetRenderDrawColor( this->GetRenderer(), 0xBB, 0xBB, 0xBB, 0xBB );
    SDL_RenderClear( this->GetRenderer() );
}

bool LWindow::IsInit()
{
    return this->_isInit;
}

bool LWindow::LoadSDLExtensions()
{
    bool success = true;
    //Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		success = false;
	}

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    return success;
}

bool LWindow::Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		this->window = SDL_CreateWindow( "ICE Engine - Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->_width, this->_height, SDL_WINDOW_SHOWN );
		if( this->window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
            this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( this->renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( this->renderer, 0xBB, 0xBB, 0xBB, 0xBB );

                //Load SDL Extensions
                success = LoadSDLExtensions();
			}
		}
	}

	return success;
}