CC = gcc
CFLAGS = -Wall -I/usr/include/SDL2 -I.
LDFLAGS = -lSDL2 -lSDL2_image
OBJ = main.o snake.o

all: snake_game

snake_game: $(OBJ)
	$(CC) -o snake_game $(OBJ) $(LDFLAGS)

main.o: main.c snake.h
	$(CC) $(CFLAGS) -c main.c

snake.o: snake.c snake.h
	$(CC) $(CFLAGS) -c snake.c

clean:
	rm -f $(OBJ) snake_game

.PHONY: all clean
