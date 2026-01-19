#include "utils.h"

#define BOARD_SIZE 10

#define CELL_CURRENT board[i][j]
#define CELL_UPPER   board[i-1][j]

enum tile {
    TILE_EMPTY = 0,
    TILE_CIRCLE,   // @
    TILE_SQUARE,   // #
    TILE_TRIANGLE, // ^
    TILE_HEART,    // &
    TILE_DIAMOND,  // $
};

enum tile board[BOARD_SIZE][BOARD_SIZE] = {0};
size_t score = 0;

void init(void);
void draw(void);
void fall(void);
bool swap(point p1, point p2);
bool matches(void);
enum tile rand_tile();
char tile_to_char(enum tile t);
colors tile_to_color(enum tile t);

int main(void)
{
    srand(time(NULL));
    init();
    return 0;
}

void init(void)
{
    fall();
}

void draw(void)
{
    char buff[(BOARD_SIZE * BOARD_SIZE) + BOARD_SIZE];
    size_t pos = 0;

    putchar('\n');
    for(size_t i = 0; i < BOARD_SIZE; ++i){
        for(size_t j = 0; j < BOARD_SIZE; ++j){
            put_colored(
                tile_to_char(board[i][j]),
                tile_to_color(board[i][j])
            );
        }
        putchar('\n');
    }
    putchar('\n');
}

void fall(void)
{
    size_t empty_cells = 0;
    do {
        empty_cells = 0;
        for(size_t i = BOARD_SIZE - 1; i != -1; --i){
            for(size_t j = 0; j < BOARD_SIZE; ++j){
                if(i == 0) CELL_CURRENT = rand_tile();
                if(CELL_CURRENT == TILE_EMPTY){
                    if(CELL_UPPER != TILE_EMPTY){
                        CELL_CURRENT = CELL_UPPER;
                        CELL_UPPER = TILE_EMPTY;
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
        draw();
        sleep(1);
    } while(empty_cells != 0);
}

bool swap(point p1, point p2)
{
    // Swap two tiles and check for matches
    return false;
}

bool matches(void)
{
    // Find and clear matches of three or more tiles
    return false;
}

enum tile rand_tile()
{
    int rnd = rand() % 5;
    switch(rnd){
        case 0: return TILE_CIRCLE;
        case 1: return TILE_SQUARE;
        case 2: return TILE_TRIANGLE;
        case 3: return TILE_HEART;
        case 4: return TILE_DIAMOND;
    }
    return '.';
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
}
