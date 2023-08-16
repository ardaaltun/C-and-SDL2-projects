//mingw32-make.exe

#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* imgSurface = NULL;
bool init();

int main( int argc, char* args[] )
{
	int r=0,g=0,b=0;
	//Create the window we'll be rendering to
	//The surface contained by the window
	init();

	//Fill the surface white
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, r, g, b) );
	
	//Update the surface
	SDL_UpdateWindowSurface( window );
    
    //Hack to get window to stay up
    SDL_Event e;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    bool quit = false;
    while( quit == false )
    {
    	while( SDL_PollEvent( &e ) )
    		{ 
    			if( e.type == SDL_QUIT )
    				quit = true;
    			if (state[SDL_SCANCODE_ESCAPE])
           			quit = true;
           		if(state[SDL_SCANCODE_Q])	r=255;	if(state[SDL_SCANCODE_A])	r=0;
	    		}
           		SDL_UpdateWindowSurface(window);

    }

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}


bool init()
{
	bool success = true;
	window = SDL_CreateWindow( "Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if(window == NULL)
	{
		printf("ERROR SDL_CreateWindow");
		success = false;
	}
	screenSurface = SDL_GetWindowSurface( window );
	if(screenSurface == NULL)
	{
		printf("ERROR SDL_Surface");
		success = false;
	}

	return success;
}