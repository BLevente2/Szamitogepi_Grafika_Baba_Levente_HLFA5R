#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float a;
    float b;
    float c;
} Brick;

Brick* CreateBrick() {
    Brick* brick = (Brick*)malloc(sizeof(Brick));
    return brick;
}

void ReadSizesFromUser(Brick* brick) {
    int valid;
    do {
        printf("Enter three edge lengths separated by spaces: ");
        valid = scanf("%f %f %f", &(brick->a), &(brick->b), &(brick->c));
        while(getchar() != '\n');
        if(valid != 3) {
            printf("Invalid input. Please try again.\n");
        }
    } while(valid != 3);
}

float CalculateVolume(Brick brick) {
    return brick.a * brick.b * brick.c;
}

float CalculateSurfaceArea(Brick brick) {
    return 2 * (brick.a * brick.b + brick.a * brick.c + brick.b * brick.c);
}

int HasSquareFace(Brick brick) {
    if(brick.a == brick.b || brick.a == brick.c || brick.b == brick.c)
        return 1;
    return 0;
}

char* BrickToString(Brick brick) {
    char* str = (char*)malloc(100 * sizeof(char));
    sprintf(str, "Brick dimensions: a = %.2f, b = %.2f, c = %.2f", brick.a, brick.b, brick.c);
    return str;
}

int main() {
    Brick* brick = CreateBrick();
    ReadSizesFromUser(brick);
    float volume = CalculateVolume(*brick);
    float surfaceArea = CalculateSurfaceArea(*brick);
    int squareFace = HasSquareFace(*brick);
    char* brickStr = BrickToString(*brick);
    printf("%s\n", brickStr);
    printf("Volume: %.2f\n", volume);
    printf("Surface Area: %.2f\n", surfaceArea);
    printf("Has Square Face: %d\n", squareFace);
    free(brick);
    free(brickStr);
    return 0;
}