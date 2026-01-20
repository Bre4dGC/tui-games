#include "utils.h"

enum tile {
    TILE_EMPTY = 0,
    TILE_CIRCLE,   // @
    TILE_SQUARE,   // #
    TILE_TRIANGLE, // ^
    TILE_HEART,    // &
    TILE_DIAMOND,  // $
};

enum tile board[BOARD_SIZE][BOARD_SIZE] = {0};
point selected = {0,0};
point cursor = {0,0};
size_t score = 0;
int empty_cells = 0;

void draw(void);
int fall(void);
bool swap(point p1, point p2);
bool matches(void);
enum tile rand_tile(void);
char tile_to_char(enum tile t);
colors tile_to_color(enum tile t);

int main(void)
{
    srand(time(NULL));
    while(true){
        while(fall() != 0){
            draw();
            empty_cells = 0;
            MSLEEP(400);
        }
        
        draw();

        switch(get_ch()){
            case 'w': MOVE_UP;    continue;
            case 'a': MOVE_LEFT;  continue;
            case 's': MOVE_DOWN;  continue;
            case 'd': MOVE_RIGHT; continue;
            case ' ': selected = cursor; break;
            case 'q': return true;
        }
    }
    return 0;
}

void draw(void)
{
    bool is_selected = false;

    putchar('\n');
    for(int y = 0; y < BOARD_SIZE; ++y){
        for(int x = 0; x < BOARD_SIZE; ++x){
            is_selected = cursor.y == y && cursor.x == x;
            is_selected ?
                printf("[%s%c\033[0m]",
                    color_code(tile_to_color(board[y][x])),
                    tile_to_char(board[y][x])
                )
                :
                printf(" %s%c\033[0m ",
                    color_code(tile_to_color(board[y][x])),
                    tile_to_char(board[y][x])
                );
        }
        putchar('\n');
    }
    putchar('\n');
}

int fall(void)
{
    for(int y = BOARD_SIZE - 1; y >= 0; --y){
        for(int x = 0; x < BOARD_SIZE; ++x){
            if(CELL_CURRENT == TILE_EMPTY && y == 0){
                CELL_CURRENT = rand_tile();
            }
            if(CELL_CURRENT == TILE_EMPTY){
                if(CELL_ABOVE != TILE_EMPTY){
                    CELL_CURRENT = CELL_ABOVE;
                    CELL_ABOVE = TILE_EMPTY;
                }
                else {
                    empty_cells++;
                    continue;
                }
            }
            if(CELL_CURRENT == TILE_EMPTY && empty_cells > 0){
                empty_cells--;
            }
        }
    }
}

bool swap(point p1, point p2)
{
    
    return false;
}

bool matches(void)
{
    // Find and clear matches of three or more tiles
    return false;
}

void destroy(void)
{

}

enum tile rand_tile(void)
{
    int rnd = rand() % 5;
    switch(rnd){
        case 0: return TILE_CIRCLE;
        case 1: return TILE_SQUARE;
        case 2: return TILE_TRIANGLE;
        case 3: return TILE_HEART;
        case 4: return TILE_DIAMOND;
    }
    return TILE_EMPTY;
}

char tile_to_char(enum tile t)
{
    switch(t){
        case TILE_EMPTY:    return '.'; 
        case TILE_CIRCLE:   return '@'; 
        case TILE_SQUARE:   return '#'; 
        case TILE_TRIANGLE: return '^'; 
        case TILE_HEART:    return '&'; 
        case TILE_DIAMOND:  return '$'; 
    }
    return '.';
}

colors tile_to_color(enum tile t)
{
    switch(t){
        case TILE_EMPTY:    return GRAY;
        case TILE_CIRCLE:   return MAGENTA;
        case TILE_SQUARE:   return GREEN;
        case TILE_TRIANGLE: return YELLOW;
        case TILE_HEART:    return RED;
        case TILE_DIAMOND:  return BLUE;
    }
    return GRAY;
}
