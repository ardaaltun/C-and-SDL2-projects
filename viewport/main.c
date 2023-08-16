//mingw32-make.exe

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_image.h>
#define SPEED_X 5;
#define SPEED_Y 5;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool init();
bool loadMedia(const char* path);
void shutdown();
SDL_Texture* loadTexture(const char* path);
//our wiindow
SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture* texture = NULL;


//Top left corner viewport

int main(int argc, char* args[])
{
	SDL_Rect topLeft = {0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
	SDL_Rect topRight = {SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
	SDL_Rect bottom = {0,SCREEN_HEIGHT/2,SCREEN_WIDTH,SCREEN_HEIGHT/2};
	SDL_RenderSetViewport(renderer, &topLeft);
	init();
	texture = loadTexture("./cube.png");
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
                 if (keycode == SDLK_q) {
                    quit = true;
                
             		}
			}
    

	    
	    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	    SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texture, NULL, &topLeft);
		SDL_RenderCopy(renderer, texture, NULL, &topRight);
		SDL_RenderCopy(renderer, texture, NULL, &bottom);

		SDL_RenderPresent(renderer);
	}
	}

	shutdown();

	return 0;
	}

bool init()
{
	bool success = true;
	IMG_Init(IMG_INIT_PNG);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow( "Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if(window == NULL)
	{
		printf("ERROR SDL_CreateWindow");
		success = false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255 );
	//screenSurface = SDL_GetWindowSurface( window );
	// if(screenSurface == NULL)
	// {
	// 	printf("ERROR SDL_Surface");
	// 	success = false;
	// }

	return success;
}

bool loadMedia(const char* path)
{
	bool success = true;
	//imgSurface = IMG_Load(path);
	texture = loadTexture(path);
	if(texture == NULL)
	{
		printf("ERROR texture");
		success = false;
	}
	//imgSurface = SDL_ConvertSurface(imgSurface, screenSurface->format,0);
	return success;
}

void shutdown()
{
	//Free loaded image
	SDL_DestroyTexture(texture);
	texture = NULL;

	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(const char* path)
{
	SDL_Texture* tex = NULL;
	SDL_Surface* surf = IMG_Load(path);
	tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	return tex;
}