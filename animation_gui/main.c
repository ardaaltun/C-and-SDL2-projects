#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MENU_WIDTH 200 // Width of the menu
#define ANIMATION_DURATION 1000 // Animation duration in milliseconds
#define TARGET_FPS 60 // Desired frames per second

typedef enum { CLOSED, OPENING, OPEN, CLOSING } MenuState;

typedef struct {
    float x;
    float y;
    float velocity;
    MenuState state;
    Uint32 start_time;
} Menu;

void initializeMenu(Menu* menu) {
    menu->x = SCREEN_WIDTH;
    menu->y = 0;
    menu->velocity = (float)MENU_WIDTH / ANIMATION_DURATION; // Calculate velocity based on duration and width
    menu->state = CLOSED;
    menu->start_time = 0;
}

void updateMenu(Menu* menu) {
    if (menu->state == OPENING || menu->state == CLOSING) {
        Uint32 current_time = SDL_GetTicks();
        float time_elapsed = (float)(current_time - menu->start_time);
        float delta = time_elapsed * menu->velocity;

        if (menu->state == OPENING) {
            if (menu->x > SCREEN_WIDTH - MENU_WIDTH) {
                menu->x -= delta;
            } else {
                menu->x = SCREEN_WIDTH - MENU_WIDTH;
                menu->state = OPEN;
            }
        } else if (menu->state == CLOSING) {
            if (menu->x < SCREEN_WIDTH) {
                menu->x += delta;
            } else {
                menu->x = SCREEN_WIDTH;
                menu->state = CLOSED;
            }
        }
    }
}

int isInsideButton(SDL_Rect buttonRect, int mouseX, int mouseY) {
    
    return (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
            mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h);
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    
    // Initialize SDL2_image for PNG loading
    IMG_Init(IMG_INIT_PNG);

    Menu gameModesMenu;
    initializeMenu(&gameModesMenu);

    int running = 1;
    SDL_Event event;

    Uint32 frame_start;
    int frame_time;

    // Load PNG image
    SDL_Surface* imageSurface = IMG_Load("./button.png");
    if (!imageSurface) {
        printf("Error loading image: %s\n", IMG_GetError());
        return 1;
    }

    // Create texture from the loaded image surface
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); // Free the surface after creating the texture

    SDL_Rect imageRect = { 20, 20, 200, 200 }; // Rectangle for the image/button

    int clicking = 0; // Flag to indicate if the button is clicked

    int mouseX, mouseY;
    while (running) {
        frame_start = SDL_GetTicks();

        
        while (SDL_PollEvent(&event)) {

            
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_p) { // Press 'p' to open submenu
                    if (gameModesMenu.state == CLOSED) {
                        gameModesMenu.state = OPENING;
                        gameModesMenu.start_time = SDL_GetTicks(); // Start time when opening
                    } else if (gameModesMenu.state == OPEN) {
                        gameModesMenu.state = CLOSING;
                        gameModesMenu.start_time = SDL_GetTicks(); // Start time when closing
                    }
                }
            }
            else if(event.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                //SDL_SetWindowTitle(window, atoi(mouseX));
                printf("%d %d", mouseX, mouseY);
            }
             else if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Log("sadasd");
                // Check if the click occurred within the button's rectangle
                if (isInsideButton(imageRect, mouseX, mouseY)) {
                    clicking = 1; // Set the clicking flag
                    SDL_Log("clicked");
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Check if the release occurred within the button's rectangle and a click was initiated
                if (clicking && isInsideButton(imageRect, mouseX, mouseY)) {
                    // Handle button click here (e.g., perform an action)
                    printf("Button clicked!\n");
                }

                clicking = 0; // Reset the clicking flag
            }
        }

        // Clear the screen with a black background
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderClear(renderer);

        // Draw main content here

        // Update the submenu
        updateMenu(&gameModesMenu);

        // Draw the submenu
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_Rect submenuRect = { (int)gameModesMenu.x, (int)gameModesMenu.y, MENU_WIDTH, SCREEN_HEIGHT };
        SDL_RenderFillRect(renderer, &submenuRect);

        // Render the image/button
        SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);

        SDL_RenderPresent(renderer);

        // Frame rate control
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < (1000 / TARGET_FPS)) {
            SDL_Delay((1000 / TARGET_FPS) - frame_time);
        }
    }

    // Cleanup
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit(); // Quit SDL2_image
    SDL_Quit();

    return 0;
}
