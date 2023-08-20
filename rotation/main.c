//mingw32-make.exe

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_image.h>
#include <time.h>
const int ANIM_SPEED = 1000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool init();
void shutdown();
void render(int x, int y, SDL_Rect rect);
void renderex(SDL_Rect* rect, SDL_Rect* dest, double angle, SDL_Point* point, SDL_RendererFlip flip);
SDL_Texture* loadTexture(const char* path);
//our wiindow
SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;
//SDL_Surface *windowSurface = NULL;


SDL_Texture* arrowsprite = NULL;
//Top left corner viewport

int main(int argc, char* args[])
{
	double angle = 90;
	SDL_Rect arrow = {0,0,250,100}; 
	SDL_Rect dest = {SCREEN_WIDTH /2 - 125 ,SCREEN_HEIGHT/2 - 50,250,100}; 
	SDL_Point point =  {arrow.w/2,arrow.h/2};
	init();
	arrowsprite = loadTexture("./arrow.png");
	//Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    int r,g,b;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
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
			}
    

	    

	    
	}
		angle+= 0.1f;
		SDL_RenderClear(renderer);

		//SDL_RenderCopyEx(renderer, arrowsprite, &arrow, &dest, angle, &point, flip);
		renderex(&arrow, &dest, angle, &point, flip);
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
	 //windowSurface= SDL_GetWindowSurface( window );

	return success;
}

void render(int x, int y, SDL_Rect rect)
{
	SDL_Rect temp = {x,y,150,150};
	SDL_RenderCopy(renderer, arrowsprite, &rect, &temp);
}

void renderex(SDL_Rect* rect, SDL_Rect* dest, double angle, SDL_Point* point, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, arrowsprite, rect, dest, angle, point, flip);
}

void shutdown()
{
	//Free loaded image
	SDL_DestroyTexture(arrowsprite);
	arrowsprite = NULL;

	//Destroy window
	//SDL_DestroySurface(windowSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );
	//windowSurface = NULL;
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