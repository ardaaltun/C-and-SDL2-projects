//mingw32-make.exe

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_image.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
#define SPEED_X 5;
#define SPEED_Y 5;

bool init();
bool loadMedia(const char* path);
void shutdown();
SDL_Texture* loadTexture(const char* path);
//our wiindow
SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture* texture = NULL;
SDL_Rect rect = {0,0,25,25};
int main(int argc, char* args[])
{
	init();
	//loadIMG("./cube.png");
	loadMedia("./cube.png");
    
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
                    rect.y -= SPEED_Y;
                } else if (keycode == SDLK_a) {
                    rect.x -= SPEED_X;
                } else if (keycode == SDLK_s) {
                	rect.y += SPEED_Y;
                } else if (keycode == SDLK_d) {
                    rect.x += SPEED_X;
                } else if (keycode == SDLK_q) {
                    quit = true;
                }

            }

	    }
	    // Clear the screen
	    //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 255, 255));
	    SDL_RenderClear(renderer);
	    // Blit the image onto the screen
	    //SDL_BlitSurface(imgSurface, NULL, screenSurface, NULL);


	    //Render texture to screen
	    SDL_RenderCopy(renderer, texture, NULL, &rect);


	    // Update the window surface
	    //SDL_UpdateWindowSurface(window);
		SDL_RenderPresent(renderer);
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