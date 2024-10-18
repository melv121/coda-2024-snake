#include <SDL.h>
#include <SDL_image.h>
#include "snake.h"

int main(int argc, char* args[]) {
    // Initialisation de SDL et SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || IMG_Init(IMG_INIT_PNG) == 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (!initGame(renderer)) {
        fprintf(stderr, "Error initializing game\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int quit = 0;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_z: changeDirection(UP); break;
                    case SDLK_s: changeDirection(DOWN); break;
                    case SDLK_q: changeDirection(LEFT); break;
                    case SDLK_d: changeDirection(RIGHT); break;
                }
            }
        }

        updateSnake();
        if (checkCollisions()) {
            printf("Game Over\n");
            // Afficher l'image "Game Over"
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000); // Afficher pendant 3 secondes
            quit = 1;
        } else {
            // DÃ©finir la couleur de fond en beige (R: 245, G: 245, B: 220, A: 255)
            SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255);
            SDL_RenderClear(renderer);
            renderGame(renderer);
        }

        SDL_Delay(150);
    }

    cleanupGame();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();

    return 0;
}