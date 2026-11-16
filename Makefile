SRC = src/main.c src/bird.c src/pipes.c src/game.c src/blocs.c src/fleches.c

flappy.exe: $(SRC)
	gcc $(SRC) -o flappy.exe $(shell pkg-config --cflags --libs raylib) -lopengl32 -lgdi32 -lwinmm

run: flappy.exe
	./flappy.exe