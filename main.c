#include "snake.h"

int main() {
	
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    	return 1;
    }

 	SDL_Window* window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
 	
 	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
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
                case SDLK_UP: changeDirection(UP); break;
                case SDLK_DOWN: changeDirection(DOWN); break;
                case SDLK_LEFT: changeDirection(LEFT); break;
                case SDLK_RIGHT: changeDirection(RIGHT); break;
            }
        }
    }

     updateSnake();
    if (checkCollisions()) {
        quit = 1;
    }
    renderGame(renderer);
    SDL_Delay(150);
}
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
return 0;
}


