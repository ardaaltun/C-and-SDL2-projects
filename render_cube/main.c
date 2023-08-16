//mingw32-make.exe

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_image.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadIMG(const char* path);
void shutdown();
 

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* imgSurface = NULL;

int main(int argc, char* args[])
{
	init();
	loadIMG("./cube.png");
	
	SDL_Rect rect;
	rect.x = 50;
	rect.y = 50;
	// //Fill the surface cyan
	//SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 255, 255) );
	//Render image
	
	
    
    //Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
	while (!quit)
	{	//will take events off the queue until it is empty 
	    while (SDL_PollEvent(&e) != 0)
	    {
	        if (e.type == SDL_QUIT)
	        {
	            quit = true;
	        }
	        else if (e.type == SDL_KEYDOWN) {
                SDL_Keycode keycode = e.key.keysym.sym;
                if (keycode == SDLK_w) {
                    printf("W pressed\n");
                } else if (keycode == SDLK_a) {
                    printf("A pressed\n");
                } else if (keycode == SDLK_s) {
                    printf("S pressed\n");
                } else if (keycode == SDLK_d) {
                    printf("D pressed\n");
                } else if (keycode == SDLK_q) {
                    quit = true;
                }

            }

	    }
	    // Clear the screen
	    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 255, 255));

	    // Blit the image onto the screen
	    SDL_BlitSurface(imgSurface, NULL, screenSurface, NULL);

	    // Update the window surface
	    SDL_UpdateWindowSurface(window);
	}

	shutdown();

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

bool loadIMG(const char* path)
{
	bool success = true;
	imgSurface = IMG_Load(path);
	if(imgSurface == NULL)
	{
		printf("ERROR imgSurface");
		success = false;
	}
	imgSurface = SDL_ConvertSurface(imgSurface, screenSurface->format,0);
	return success;
}

void shutdown()
{
	//Deallocate surface
	SDL_FreeSurface(imgSurface);
	imgSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}