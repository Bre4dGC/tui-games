#include "utils.h"

typedef enum {EMPTY, APPLE, SNAKE} cell;

typedef struct {
    point head;
    point body[100];
    size_t len;
    direction direction;
} snake;

void draw(cell** board);
void move(snake* snk, direction direction);
void random(point* pt);

int main(void)
{
    cell board[BOARD_SIZE][BOARD_SIZE] = {0};
    snake snake = {{0,0},{0},1};
    point apple = {0,0};
    bool is_over = false;
    
    random(&snake.head);
    random(&apple);

    do {
        draw(board);
        MSLEEP(200);
        if(IS_KEY_PRESSED){
            move(&snake, snake.direction);
            continue;
        }
        switch(get_ch()){
            case 'w': snake.direction = UP;    break;
            case 'a': snake.direction = LEFT;  break;
            case 's': snake.direction = DOWN;  break;
            case 'd': snake.direction = RIGHT; break;
            case 'q': is_over = true;
        }
        move(&snake, snake.direction);
    } while(!is_over);
    return 0;
}

void draw(cell** board)
{
    for(size_t y = 0; y < BOARD_SIZE; y++){
        for(size_t x = 0; x < BOARD_SIZE; x++){
            board[y][x] = EMPTY;
        }
        printf("\n");
    }
}

void move(snake* snake, direction direction)
{

}

void random(point* pt)
{

}
