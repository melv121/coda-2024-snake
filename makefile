CC=gcc
CFLAGS=-Wall -I/usr/include/SDL2 -I.
LDFLAGS=-L/usr/lib -lSDL2
EXEC=snake_game

all: $(EXEC)

$(EXEC): main.o snake.o
	$(CC) -o $(EXEC) main.o snake.o $(LDFLAGS)

main.o: main.c snake.h
	$(CC) $(CFLAGS) -c main.c

snake.o: snake.c snake.h
	$(CC) $(CFLAGS) -c snake.c

clean:
	rm -f *.o $(EXEC)

.PHONY: clean
