#include "snake.h"

Snake snake;
Food food;

int initGame(SDL_Renderer* renderer) {
    srand(time(NULL));
    initSnake();
    placeFood();
    return 1;
}
void initSnake() {
    snake.length = 1;
    snake.body[0].x = GRID_WIDTH / 2;
    snake.body[0].y = GRID_HEIGHT / 2;
    snake.direction = RIGHT;
}
void placeFood() {
    food.position.x = rand() % GRID_WIDTH;
    food.position.y = rand() % GRID_HEIGHT;
}
void updateSnake() {
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }
    switch (snake.direction) {
        case UP: snake.body[0].y -= 1; break;
        case DOWN: snake.body[0].y += 1; break;
        case LEFT: snake.body[0].x -= 1; break;
        case RIGHT: snake.body[0].x += 1; break;
    }
    
    if (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y) {
        snake.length++;
        placeFood();
    }
}
int checkCollisions() {
    Position head = snake.body[0];
   
    if (head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT) {
        return 1;
    }
   
    for (int i = 1; i < snake.length; i++) {
        if (head.x == snake.body[i].x && head.y == snake.body[i].y) {
            return 1;
        }
    }
    return 0;
}
void renderGame(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
    for (int i = 0; i < snake.length; i++) {
        SDL_Rect rect = {snake.body[i].x * TILE_SIZE, snake.body[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_Rect foodRect = {food.position.x * TILE_SIZE, food.position.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_RenderFillRect(renderer, &foodRect);
    SDL_RenderPresent(renderer);
}
void cleanupGame() {
    
}
void changeDirection(Direction newDirection) {
    
    if ((newDirection == UP && snake.direction != DOWN) ||
        (newDirection == DOWN && snake.direction != UP) ||
        (newDirection == LEFT && snake.direction != RIGHT) ||
        (newDirection == RIGHT && snake.direction != LEFT)) {
        snake.direction = newDirection;
    }
return 0;
}
