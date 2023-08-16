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
void shutdown();
SDL_Texture* loadTexture(const char* path);
//our wiindow
SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture* charTexture = NULL;
SDL_Texture* bgTexture = NULL;


//Top left corner viewport

int main(int argc, char* args[])
{
	SDL_Rect charRect = {220,220,50,100};
	SDL_Rect bgRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	init();
	charTexture = loadTexture("./char.png");
	bgTexture = loadTexture("./bg.png");
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
                 if (keycode == SDLK_q)	quit = true;
				 else if(keycode == SDLK_a) charRect.x--;
				 else if(keycode == SDLK_d) charRect.x++;
				 else if(keycode == SDLK_w) charRect.y--;
				 else if(keycode == SDLK_s) charRect.y++;

			}
    

	    
	    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	    SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, bgTexture, NULL, &bgRect);
		SDL_RenderCopy(renderer, charTexture, NULL, &charRect);

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

void shutdown()
{
	//Free loaded image
	SDL_DestroyTexture(charTexture);
	charTexture = NULL;
	SDL_DestroyTexture(bgTexture);
	bgTexture = NULL;

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
 	SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB( surf->format, 0xFF, 0xFF, 0xFF));
	tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	//Color key image
	return tex;
}