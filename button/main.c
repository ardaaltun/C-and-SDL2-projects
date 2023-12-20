#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum ButtonState { NORMAL, HOVERED, CLICKED };

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        printf("Failed to load image! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load textures for button states
    SDL_Texture* textureNormal = loadTexture(renderer, "button.png");
    SDL_Texture* textureHovered = loadTexture(renderer, "button2.png");
    SDL_Texture* textureClicked = loadTexture(renderer, "button3.png");

    if (!textureNormal || !textureHovered || !textureClicked) {
        return 1; // Failed to load textures
    }

    enum ButtonState buttonState = NORMAL;

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    buttonState = CLICKED;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;

                // Check if the mouse is over the button to change its state
                // Replace buttonRect with your button's rect coordinates
                SDL_Rect buttonRect = { /* button's x, y, width, height */ };
                if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
                    mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
                    buttonState = HOVERED;
                } else {
                    buttonState = NORMAL;
                }
            }
        }

        SDL_RenderClear(renderer);

        // Render the button based on its state
        switch (buttonState) {
            case NORMAL:
                SDL_RenderCopy(renderer, textureNormal, NULL, NULL); // Replace NULL with button's rect if needed
                break;
            case HOVERED:
                SDL_RenderCopy(renderer, textureHovered, NULL, NULL); // Replace NULL with button's rect if needed
                break;
            case CLICKED:
                SDL_RenderCopy(renderer, textureClicked, NULL, NULL); // Replace NULL with button's rect if needed
                break;
            default:
                break;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textureNormal);
    SDL_DestroyTexture(textureHovered);
    SDL_DestroyTexture(textureClicked);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
