//mingw32-make.exe

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL_image.h>
#include <time.h>
#include <SDL_ttf.h>
const int ANIM_SPEED = 1000;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool init();
void shutdown();
void render(int x, int y, SDL_Rect rect);
void renderex(SDL_Rect* rect, SDL_Rect* dest, double angle, SDL_Point* point, SDL_RendererFlip flip);
SDL_Texture* loadTexture(const char* path);
SDL_Texture* type(char* msg, SDL_Color color);
//our wiindow
SDL_Window* window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font* font = NULL;
SDL_Texture* texture = NULL;
SDL_Surface *msgSurface = NULL;
//Top left corner viewport
int x,y;

int main(int argc, char* args[])
{
	init();
	font = TTF_OpenFont("arial.ttf",24);
	
	if(font == NULL)
		printf(">>%s", TTF_GetError());
    SDL_Color black = {0,0,0,255};
	msgSurface = TTF_RenderText_Solid(font, "Hello World", black);
	texture = SDL_CreateTextureFromSurface(renderer, msgSurface);
	SDL_Rect rect = {0,0,300,100};
	SDL_Rect dest = {0,0,300,100}; 
	//Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    //texture = type("Hello World!", black);
	
	while (!quit)
	{	//will take events off the queue until it is empty 
	    while (SDL_PollEvent(&e) != 0)
	    {
	        if (e.type == SDL_QUIT)
	        {
	            quit = true;
	        }
	        else if(e.type == SDL_MOUSEMOTION)
	        {
	        	SDL_GetMouseState(&x, &y);
	        	// Convert mouse coordinates to string
		        char mouseCoords[32]; // Big enough to hold the coordinates as string
		        snprintf(mouseCoords, sizeof(mouseCoords), "x: %d, y: %d", x,y);
				msgSurface = TTF_RenderText_Solid(font, mouseCoords, black);
				texture = SDL_CreateTextureFromSurface(renderer, msgSurface);
	        	
	        }
	        else if (e.type == SDL_KEYDOWN) {
                 SDL_Keycode keycode = e.key.keysym.sym;
                 if (keycode == SDLK_q)	quit = true;
			}
    

	    

	    
	}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, &rect, &dest);
		SDL_RenderPresent(renderer);
		
	}

	shutdown();

	return 0;
	}

bool init()
{
	bool success = true;
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	if(!TTF_Init())
		printf("%s\n", TTF_GetError());

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow( "Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if(window == NULL)
	{
		printf("ERROR SDL_CreateWindow");
		success = false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255 );

	return success;
}


SDL_Texture* type(char* msg, SDL_Color color)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, msg, color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return tex;
}

void shutdown()
{
	//Free loaded image
	SDL_DestroyTexture(texture);
	texture = NULL;
	//SDL_DestroySurface(msgSurface);
	msgSurface = NULL;
	TTF_CloseFont(font);
	font = NULL;
	//Destroy window
	//SDL_DestroySurface(windowSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow( window );
	//windowSurface = NULL;
	window = NULL;
	renderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
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