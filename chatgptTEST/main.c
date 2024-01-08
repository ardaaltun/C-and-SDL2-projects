#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int main(int argc, char* args[])
{
    // Initialize SDL and SDL_ttf

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();


    SDL_Window* window = SDL_CreateWindow("HGel", 110, 110, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Load the font
    TTF_Font *font = TTF_OpenFont("E:\\_DESKTOP APPS\\GitHub Projects\\C-and-SDL2-projects\\chatgptTEST\\arial.ttf", 24); // Change the path and size as needed


    SDL_Surface* tempSurface2 = IMG_Load("E:\\_DESKTOP APPS\\GitHub Projects\\C-and-SDL2-projects\\chatgptTEST\\button.png");
    SDL_Texture* texture; // Assume you have your texture already initialized

    texture = SDL_CreateTextureFromSurface(renderer, tempSurface2);
    SDL_FreeSurface(tempSurface2);
    

    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    SDL_Log("Texture width: %d, height: %d\n", textureWidth, textureHeight);




    if (font == NULL) {
        fprintf(stderr, "Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    // Text to render
    const char *text = "Hello, SDL_ttf!";
    SDL_Color color = {255, 255, 255, 255}; // White color, change as needed
    SDL_Surface *tempSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    size_t stringSize = strlen(text) + 1;
    //SDL_Log("%d", stringSize);
    SDL_Rect dest = {0,0, stringSize * 10, stringSize * 2};
    int quit = 0;
    SDL_Event event;
    while (!quit)
    {

        while (SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
            {
                quit = 1;
                break;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);
        
        // Render text on a surface to get the dimensions
        SDL_RenderCopy(renderer, textTex, NULL, &dest);

        SDL_RenderPresent(renderer);
        
    }

    // Clean up
    TTF_CloseFont(font);
    SDL_DestroyTexture(textTex);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
