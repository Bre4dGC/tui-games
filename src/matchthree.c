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
point cursor = {-1,-1};
point selected = {-1,-1};
size_t score = 0;
size_t addition_score = 0;
int empty_cells = 0;

void draw(void);
int fall(void);
bool swap(void);
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
            MSLEEP(200);
        }

        if(POINT_CMP(cursor, ((point){-1,-1}))) cursor = ((point){0,0});

        draw();
        if(matches()) continue;

        score += addition_score;
        addition_score = 0;

        switch(getch()){
            case 'w': MOVE_UP;    continue;
            case 'a': MOVE_LEFT;  continue;
            case 's': MOVE_DOWN;  continue;
            case 'd': MOVE_RIGHT; continue;
            case ' ':
                if(POINT_CMP(selected, ((point){-1,-1}))){
                    selected = cursor;
                }
                else {
                    swap();
                    selected = (point){-1,-1};
                }
                break;
            case 'q': return true;
        }
    }
    return 0;
}

void draw(void)
{
    printf("\nScore: %-*zu", (BOARD_SIZE * 2) - (addition_score < 100 ? 1 : 2), score);
    if(addition_score != 0) printf("+%lu", addition_score);

    putchar('\n');
    for(int y = 0; y < BOARD_SIZE; ++y){
        for(int x = 0; x < BOARD_SIZE; ++x){
            if(POINT_CMP(cursor, ((point){y,x}))) printf("[");
            else printf(" ");

            put_colored(tile_to_char(CELL_CURRENT), tile_to_color(CELL_CURRENT));

            if(POINT_CMP(cursor, ((point){y,x}))) printf("]");
            else printf(" ");
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
    return empty_cells;
}

bool swap(void)
{
    point target = selected;
    if(cursor.y == selected.y && cursor.x == selected.x){
        return false;
    }
    else if(cursor.y == selected.y - 1 && cursor.x == selected.x){
        target.y--;
    }
    else if(cursor.y == selected.y + 1 && cursor.x == selected.x){
        target.y++;
    }
    else if(cursor.y == selected.y && cursor.x == selected.x - 1){
        target.x--;
    }
    else if(cursor.y == selected.y && cursor.x == selected.x + 1){
        target.x++;
    }
    else {
        return false;
    }

    enum tile temp = board[selected.y][selected.x];
    board[selected.y][selected.x] = board[target.y][target.x];
    board[target.y][target.x] = temp;

    draw();
    MSLEEP(200);

    if(!matches()){
        temp = board[selected.y][selected.x];
        board[selected.y][selected.x] = board[target.y][target.x];
        board[target.y][target.x] = temp;
        return false;
    }
    return true;
}

bool matches(void)
{
    bool found_match = false;

    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE - 2; ++x) {
            if (CELL_CURRENT != TILE_EMPTY &&
                CELL_CURRENT == CELL_RIGHT &&
                CELL_CURRENT == board[y][x + 2]) {
                found_match = true;
                enum tile temp = CELL_CURRENT;
                for (int k = 0; x + k < BOARD_SIZE && board[y][x + k] == temp; ++k) {
                    board[y][x + k] = TILE_EMPTY;
                    addition_score += 10;
                }
                for (int k = 1; x - k >= 0 && board[y][x - k] == temp; ++k) {
                    board[y][x - k] = TILE_EMPTY;
                    addition_score += 10;
                }
                MSLEEP(200);
            }
        }
    }

    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE - 2; ++y) {
            if (CELL_CURRENT != TILE_EMPTY &&
                CELL_CURRENT == CELL_BOTTOM &&
                CELL_CURRENT == board[y + 2][x]) {
                found_match = true;
                enum tile temp = CELL_CURRENT;
                for (int k = 0; y + k < BOARD_SIZE && board[y + k][x] == temp; ++k) {
                    board[y + k][x] = TILE_EMPTY;
                    addition_score += 10;
                }
                for (int k = 1; y - k >= 0 && board[y - k][x] == temp; ++k) {
                    board[y - k][x] = TILE_EMPTY;
                    addition_score += 10;
                }
                MSLEEP(200);
            }
        }
    }

    return found_match;
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
