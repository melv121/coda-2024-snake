#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define TILE_SIZE 20
#define GRID_WIDTH (WINDOW_WIDTH / TILE_SIZE)
#define GRID_HEIGHT (WINDOW_HEIGHT / TILE_SIZE)

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position body[GRID_WIDTH * GRID_HEIGHT];
    int length;
    Direction direction;
} Snake;

typedef struct {
    Position position;
} Food;

extern Snake snake;
extern Food food;
extern SDL_Texture* gameOverTexture;
extern SDL_Texture* headUpTexture;
extern SDL_Texture* headRightTexture;
extern SDL_Texture* headDownTexture;
extern SDL_Texture* headLeftTexture;
extern SDL_Texture* bodyVerticalTexture;
extern SDL_Texture* bodyHorizontalTexture;
extern SDL_Texture* bodyTopRightTexture;
extern SDL_Texture* bodyTopLeftTexture;
extern SDL_Texture* bodyBottomRightTexture;
extern SDL_Texture* bodyBottomLeftTexture;
extern SDL_Texture* tailUpTexture;
extern SDL_Texture* tailRightTexture;
extern SDL_Texture* tailDownTexture;
extern SDL_Texture* tailLeftTexture;
extern SDL_Texture* foodTexture;
extern SDL_Texture* wallTexture;

int initGame(SDL_Renderer* renderer);
void initSnake();
void placeFood();
void updateSnake();
int checkCollisions();
void renderGame(SDL_Renderer* renderer);
void cleanupGame();
void changeDirection(Direction newDirection);

#endif