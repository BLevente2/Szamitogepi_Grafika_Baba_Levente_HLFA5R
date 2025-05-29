CC       := gcc
CFLAGS   := -Iinclude -Wall -Wextra -Wpedantic -std=c99

ifneq ($(wildcard include/obj),)
CFLAGS  += -Iinclude/obj
else
CFLAGS  += -I/mingw/include/obj
endif

SRC      := \
    src/app.c \
    src/camera.c \
    src/control.c \
    src/coin.c \
    src/font.c \
    src/main.c \
    src/physics.c \
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

ifneq ($(wildcard lib/libobj.a),)
OBJ_LIB  := lib/libobj.a
else
OBJ_LIB  := /mingw/lib/libobj.a
endif

LIBS_WIN := $(OBJ_LIB) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lglu32 -lgdi32 -lm -lsetupapi -lole32 -loleaut32 -limm32 -lversion -lwinmm -luuid
LIBS_LIN := -lSDL2 -lSDL2_image -lGL -lGLU -lm

.PHONY: all linux clean

all: CubestacleSDL.exe

CubestacleSDL.exe: $(SRC)
	$(CC) $(CFLAGS) -static $(SRC) $(LIBS_WIN) -o $@

linux: CubestacleSDL

CubestacleSDL: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIBS_LIN) -o $@

clean:
	rm -f CubestacleSDL.exe CubestacleSDL