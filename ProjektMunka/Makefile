CC       := gcc
CFLAGS   := -Iinclude -Wall -Wextra -Wpedantic -std=c99

SRC      := \
    src/app.c \
    src/camera.c \
    src/coin.c \
    src/main.c \
    src/scene.c \
    src/utils.c \
    src/rectangular_prism.c \
    src/player.c \
    src/ground.c \
    src/skybox.c \
    src/obstacle.c \
    src/menu.c \
    src/gameover.c \
    src/info.c

LIBS_WIN := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglu32 -lgdi32 -lm
LIBS_LIN := -lSDL2 -lSDL2_image -lGL -lGLU -lm

.PHONY: all linux clean

all: CubestacleSDL.exe

CubestacleSDL.exe: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS_WIN) -o $@

linux: CubestacleSDL

CubestacleSDL: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS_LIN) -o $@

clean:
	rm -f CubestacleSDL CubestacleSDL.exe
