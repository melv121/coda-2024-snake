#include "snake.h"
#include <SDL2/SDL_image.h>

Snake snake;
Food food;
SDL_Texture* gameOverTexture;
SDL_Texture* headUpTexture;
SDL_Texture* headRightTexture;
SDL_Texture* headDownTexture;
SDL_Texture* headLeftTexture;
SDL_Texture* bodyVerticalTexture;
SDL_Texture* bodyHorizontalTexture;
SDL_Texture* bodyTopRightTexture;
SDL_Texture* bodyTopLeftTexture;
SDL_Texture* bodyBottomRightTexture;
SDL_Texture* bodyBottomLeftTexture;
SDL_Texture* tailUpTexture;
SDL_Texture* tailRightTexture;
SDL_Texture* tailDownTexture;
SDL_Texture* tailLeftTexture;
SDL_Texture* foodTexture;
SDL_Texture* wallTexture;

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    if (texture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    }
    return texture;
}

int initGame(SDL_Renderer* renderer) {
    srand(time(NULL));
    initSnake();
    placeFood();

    gameOverTexture = loadTexture("game_over.png", renderer);
    if (!gameOverTexture) return 0;

    headUpTexture = loadTexture("head_up.png", renderer); //debut chat gpt
    headRightTexture = loadTexture("head_right.png", renderer);
    headDownTexture = loadTexture("head_down.png", renderer);
    headLeftTexture = loadTexture("head_left.png", renderer);
    if (!headUpTexture || !headRightTexture || !headDownTexture || !headLeftTexture) return 0;

    bodyVerticalTexture = loadTexture("body_vertical.png", renderer);
    bodyHorizontalTexture = loadTexture("body_horizontal.png", renderer);
    bodyTopRightTexture = loadTexture("body_topright.png", renderer);
    bodyTopLeftTexture = loadTexture("body_topleft.png", renderer);
    bodyBottomRightTexture = loadTexture("body_bottomright.png", renderer);
    bodyBottomLeftTexture = loadTexture("body_bottomleft.png", renderer);
    if (!bodyVerticalTexture || !bodyHorizontalTexture || !bodyTopRightTexture || !bodyTopLeftTexture || !bodyBottomRightTexture || !bodyBottomLeftTexture) return 0;

    tailUpTexture = loadTexture("tail_up.png", renderer);
    tailRightTexture = loadTexture("tail_right.png", renderer);
    tailDownTexture = loadTexture("tail_down.png", renderer);
    tailLeftTexture = loadTexture("tail_left.png", renderer);
    if (!tailUpTexture || !tailRightTexture || !tailDownTexture || !tailLeftTexture) return 0;//fin chat gpt

    foodTexture = loadTexture("food.png", renderer);
    if (!foodTexture) return 0;

    wallTexture = loadTexture("Wall.png", renderer);
    if (!wallTexture) return 0;

    return 1;
}

void initSnake() {
    snake.length = 1;
    snake.body[0].x = GRID_WIDTH / 2;
    snake.body[0].y = GRID_HEIGHT / 2;
    snake.direction = RIGHT;
}

void placeFood() {
    int validPosition = 0;
    while (!validPosition) {
        food.position.x = 1 + rand() % (GRID_WIDTH - 2);
        food.position.y = 1 + rand() % (GRID_HEIGHT - 2);
        validPosition = 1;

        
        for (int i = 0; i < snake.length; i++) {
            if (food.position.x == snake.body[i].x && food.position.y == snake.body[i].y) {
                validPosition = 0;
                break;
            }
        }
    }
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

    // Vérifier si le serpent mange la nourriture
    if (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y) {
        snake.length++;
        placeFood();
    }
}

int checkCollisions() {
    
    if (snake.body[0].x < 1 || snake.body[0].x >= GRID_WIDTH - 1 ||
        snake.body[0].y < 1 || snake.body[0].y >= GRID_HEIGHT - 1) {
        return 1;
    }

    // Vérifier les collisions avec le corps du serpent
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            return 1;
        }
    }

    return 0;
}

void renderGame(SDL_Renderer* renderer) {
    // Rendre les murs
    SDL_Rect wallRect;
    for (int x = 0; x < GRID_WIDTH; x++) {
        wallRect = (SDL_Rect){x * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
        SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
        wallRect = (SDL_Rect){x * TILE_SIZE, (GRID_HEIGHT - 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
    }
    for (int y = 0; y < GRID_HEIGHT; y++) {
        wallRect = (SDL_Rect){0, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
        wallRect = (SDL_Rect){(GRID_WIDTH - 1) * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
    }

    // Rendre la tête du serpent
    SDL_Rect headRect = {snake.body[0].x * TILE_SIZE, snake.body[0].y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    switch (snake.direction) {
        case UP: SDL_RenderCopy(renderer, headUpTexture, NULL, &headRect); break;
        case RIGHT: SDL_RenderCopy(renderer, headRightTexture, NULL, &headRect); break;
        case DOWN: SDL_RenderCopy(renderer, headDownTexture, NULL, &headRect); break;
        case LEFT: SDL_RenderCopy(renderer, headLeftTexture, NULL, &headRect); break;
    }

   
    for (int i = 1; i < snake.length - 1; i++) { //debut chat gpt
        SDL_Rect bodyRect = {snake.body[i].x * TILE_SIZE, snake.body[i].y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        Direction prevDirection = (snake.body[i].x == snake.body[i - 1].x) ? (snake.body[i].y > snake.body[i - 1].y ? UP : DOWN) : (snake.body[i].x > snake.body[i - 1].x ? LEFT : RIGHT);
        Direction nextDirection = (snake.body[i].x == snake.body[i + 1].x) ? (snake.body[i].y > snake.body[i + 1].y ? UP : DOWN) : (snake.body[i].x > snake.body[i + 1].x ? LEFT : RIGHT);

        if ((prevDirection == UP && nextDirection == DOWN) || (prevDirection == DOWN && nextDirection == UP)) {
            SDL_RenderCopy(renderer, bodyVerticalTexture, NULL, &bodyRect);
        } else if ((prevDirection == LEFT && nextDirection == RIGHT) || (prevDirection == RIGHT && nextDirection == LEFT)) {
            SDL_RenderCopy(renderer, bodyHorizontalTexture, NULL, &bodyRect);
        } else if ((prevDirection == UP && nextDirection == RIGHT) || (prevDirection == RIGHT && nextDirection == UP)) {
            SDL_RenderCopy(renderer, bodyTopRightTexture, NULL, &bodyRect);
        } else if ((prevDirection == UP && nextDirection == LEFT) || (prevDirection == LEFT && nextDirection == UP)) {
            SDL_RenderCopy(renderer, bodyTopLeftTexture, NULL, &bodyRect);
        } else if ((prevDirection == DOWN && nextDirection == RIGHT) || (prevDirection == RIGHT && nextDirection == DOWN)) {
            SDL_RenderCopy(renderer, bodyBottomRightTexture, NULL, &bodyRect);
        } else if ((prevDirection == DOWN && nextDirection == LEFT) || (prevDirection == LEFT && nextDirection == DOWN)) {
            SDL_RenderCopy(renderer, bodyBottomLeftTexture, NULL, &bodyRect);
        }
    }

    
    SDL_Rect tailRect = {snake.body[snake.length - 1].x * TILE_SIZE, snake.body[snake.length - 1].y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    Direction tailDirection = (snake.body[snake.length - 1].x == snake.body[snake.length - 2].x) ? 
        (snake.body[snake.length - 1].y > snake.body[snake.length - 2].y ? DOWN : UP) : 
        (snake.body[snake.length - 1].x > snake.body[snake.length - 2].x ? RIGHT : LEFT);
    switch (tailDirection) {
        case UP: SDL_RenderCopy(renderer, tailUpTexture, NULL, &tailRect); break;
        case RIGHT: SDL_RenderCopy(renderer, tailRightTexture, NULL, &tailRect); break;
        case DOWN: SDL_RenderCopy(renderer, tailDownTexture, NULL, &tailRect); break;
        case LEFT: SDL_RenderCopy(renderer, tailLeftTexture, NULL, &tailRect); break;//fin chat gpt
    }

    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_Rect foodRect = {food.position.x * TILE_SIZE, food.position.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_RenderCopy(renderer, foodTexture, NULL, &foodRect);

    SDL_RenderPresent(renderer);
}

void cleanupGame() {
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(headUpTexture);
    SDL_DestroyTexture(headRightTexture);
    SDL_DestroyTexture(headDownTexture);
    SDL_DestroyTexture(headLeftTexture);
    SDL_DestroyTexture(bodyVerticalTexture);
    SDL_DestroyTexture(bodyHorizontalTexture);
    SDL_DestroyTexture(bodyTopRightTexture);
    SDL_DestroyTexture(bodyTopLeftTexture);
    SDL_DestroyTexture(bodyBottomRightTexture);
    SDL_DestroyTexture(bodyBottomLeftTexture);
    SDL_DestroyTexture(tailUpTexture);
    SDL_DestroyTexture(tailRightTexture);
    SDL_DestroyTexture(tailDownTexture);
    SDL_DestroyTexture(tailLeftTexture);
    SDL_DestroyTexture(foodTexture);
    SDL_DestroyTexture(wallTexture);
}

void changeDirection(Direction newDirection) {
    if ((newDirection == UP && snake.direction != DOWN) ||
        (newDirection == DOWN && snake.direction != UP) ||
        (newDirection == LEFT && snake.direction != RIGHT) ||
        (newDirection == RIGHT && snake.direction != LEFT)) {
        snake.direction = newDirection;
    }
}