all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c src/sphere.c src/cylinder.c src/cone.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm -o origin.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c src/sphere.c src/cylinder.c src/cone.c -lSDL2 -lSDL2_image -lGL -lm -o origin -Wall -Wextra -Wpedantic
