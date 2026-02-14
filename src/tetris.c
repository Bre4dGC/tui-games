#include "utils.h"

#define SHAPE_SIZE (3)

char shape[SHAPE_SIZE][SHAPE_SIZE] = {
    {0,1,1},
    {0,1,0},
    {0,1,0}
};

char rotated[SHAPE_SIZE][SHAPE_SIZE];

void draw(const char shape[SHAPE_SIZE][SHAPE_SIZE])
{
    for(int i = 0; i < SHAPE_SIZE; ++i){
        for(int j = 0; j < SHAPE_SIZE; ++j){
            printf("%c", shape[i][j] == 1 ? '#' : ' ');
        }
        printf("\n");
    }
    printf("\n");
}

void rotate(void)
{
    for(int i = 0; i < SHAPE_SIZE; ++i){
        for(int j = 0; j < SHAPE_SIZE; ++j){
            rotated[i][j] = shape[j][(SHAPE_SIZE - 1) - i];
        }
    }
    memcpy(shape, rotated, SHAPE_SIZE * SHAPE_SIZE);
    draw(rotated);
}

int main(void)
{
    rotate();
    rotate();
    rotate();
    rotate();
    return 0;
}
