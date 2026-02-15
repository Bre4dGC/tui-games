#include "utils.h"

typedef struct {
    point pos;
    direction dir;
} snake_body;

typedef struct {
    point head;
    snake_body body[BOARD_SIZE * BOARD_SIZE];
    size_t len;
    direction dir;
} snake;

point apple = {.y = 0, .x = 0};

void draw(snake snake);
bool move(snake* snk);
void random(point* pt);
char snake_head_char(snake snake);
char snake_body_char(snake_body body);

int main(void)
{
    snake snake = {.head = {5,5}, .body = {0}, .len = 0, .dir = UP};
    
    srand(time(NULL));
    set_nonblock_mode();

    random(&apple);

    do {
        draw(snake);
        MSLEEP(300);
        switch(is_key_pressed()){
            case 'w': if(snake.dir != DOWN) snake.dir = UP;    break;
            case 'a': if(snake.dir != RIGHT)snake.dir = LEFT;  break;
            case 's': if(snake.dir != UP)   snake.dir = DOWN;  break;
            case 'd': if(snake.dir != LEFT) snake.dir = RIGHT; break;
            case 'q': return 0;
        }
    } while(move(&snake));
    return 0;
}

void draw(snake snake)
{
    point pos = {.y = 0, .x = 0};

    printf("\nSnake Length: %zu\n", snake.len + 1);
    for(pos.y = 0; pos.y < BOARD_SIZE; pos.y++){
        for(pos.x = 0; pos.x < BOARD_SIZE; pos.x++){
            if(POINT_CMP(pos, apple)){
                PRINT_C_RED('@');
                continue;
            }
            if(POINT_CMP(pos, snake.head)){
                PRINT_C_GREEN(snake_head_char(snake));
                continue;
            }
            for(size_t i = 0; i < snake.len; i++){
                if(POINT_CMP(pos, snake.body[i].pos)){
                    PRINT_C_GREEN(snake_body_char(snake.body[i]));
                    goto govnocode;
                }
            }
            PRINT_C_GRAY('.');
            govnocode:
        }
        printf("\n");
    }
}

bool move(snake* snake)
{
    if(!snake) return false;

    point new_head = snake->head;
    
    switch(snake->dir)
    {
        case UP:    new_head.y--; break;
        case DOWN:  new_head.y++; break;
        case LEFT:  new_head.x--; break;
        case RIGHT: new_head.x++; break;
        default:    return false;
    }

    if(new_head.x < 0 || new_head.x >= BOARD_SIZE || new_head.y < 0 || new_head.y >= BOARD_SIZE){
        return false;
    }
    
    for(size_t i = 0; i < snake->len; i++){
        if(POINT_CMP(new_head, snake->body[i].pos)){
            return false;
        }
    }

    if(POINT_CMP(new_head, apple)){
        random(&apple);
        snake->body[snake->len++].pos = new_head;
    }

    if(snake->len > 0){
        for(size_t i = snake->len; i > 0; i--){
            snake->body[i] = snake->body[i-1];
        }
        snake->body[0].pos = snake->head;
        snake->body[0].dir = snake->dir;
    }

    snake->head = new_head;
    return true;
}

void random(point* pt)
{
    if(!pt) return;
    pt->x = rand() % BOARD_SIZE;
    pt->y = rand() % BOARD_SIZE;
}

char snake_head_char(snake snake)
{
    switch(snake.dir)
    {
        case UP:    return '^';
        case LEFT:  return '<';
        case DOWN:  return 'v';
        case RIGHT: return '>';
    }
}

char snake_body_char(snake_body body)
{
    switch(body.dir)
    {
        case UP:
        case DOWN:
            return body.pos.y % 2 == 0 ? '\\' : '/';
        case LEFT:
        case RIGHT:
            return body.pos.x % 2 == 0 ? '-' : '^';
    }
}
