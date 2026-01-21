#include "utils.h"

#define LENGTH    (10)
#define NUMBER_OF_BOMB (10)
#define EMPTY   (0)
#define BOMB    (-1)
#define FLAGGED (-2)
#define HIDDEN  (-3)

int board[LENGTH][LENGTH] = {0};
point bomb_coords[NUMBER_OF_BOMB] = {0};
point cursor = {1,1};

void init(void);
void draw(void);
bool open(int x, int y);
bool do_action(void);
bool is_bomb(int x, int y);
int count_adjacent_bombs(int x, int y);
void display_bombs(void);

int main(void)
{
    srand(time(NULL));
    bool is_gameover = false;

    init();
    while(!is_gameover){
        draw();
        is_gameover = do_action();
    }
    
    display_bombs();
    draw();

    return EXIT_SUCCESS;
}

void init(void)
{
    for(int y = 0; y < LENGTH; ++y){
        for(int x = 0; x <= LENGTH; ++x){
            board[y][x] = HIDDEN;
        }
    }

    for(int i = 0; i <= NUMBER_OF_BOMB; ++i){
        int x, y;
        do {
            x = rand() % LENGTH;
            y = rand() % LENGTH;
        } while (is_bomb(x, y));

        bomb_coords[i].x = x;
        bomb_coords[i].y = y;
    }
}

void draw(void)
{
    bool is_selected;
    char ch;
    for(int y = 0; y < LENGTH; ++y){
        for(int x = 0; x < LENGTH; ++x){
            is_selected = cursor.y == y && cursor.x == x;
            switch(board[y][x]){
                case HIDDEN:  ch = '.'; break;
                case EMPTY:   ch = ' '; break;
                case FLAGGED: ch = 'F'; break;
                case BOMB:    ch = '*'; break;
                default: ch = board[y][x] + '0'; break;
            }
            is_selected ? printf("[%c]", ch) : printf(" %c ", ch);
        }
        putchar('\n');
    }
    putchar('\n');
}

bool open(int x, int y)
{
    if(x < 0 || x >= LENGTH || y < 0 || y >= LENGTH) return false;
    if(board[y][x] != HIDDEN && board[y][x] != FLAGGED) return false;
    if(is_bomb(x, y)) return true;
    
    int count = count_adjacent_bombs(x, y);
    board[y][x] = count;

    if(count == 0){
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                open(x + dx, y + dy);
            }
        }
    }

    return false;
}

bool do_action(void)
{
    switch(get_ch()){
        case 'w': MOVE_UP;    break;
        case 'a': MOVE_LEFT;  break;
        case 's': MOVE_DOWN;  break;
        case 'd': MOVE_RIGHT; break;
        case 'q': return true;
        case 'f':
            board[cursor.y][cursor.x] = board[cursor.y][cursor.x] == HIDDEN ? FLAGGED : HIDDEN;
            break;
        case ' ': 
            if(board[cursor.y][cursor.x] == HIDDEN)
                return open(cursor.x, cursor.y);
            break;
        default: break;
    }
    return false;
}

bool is_bomb(int x, int y)
{
    for(int i = 0; i < NUMBER_OF_BOMB; ++i){
        if(x == bomb_coords[i].x && y == bomb_coords[i].y){
            return true;
        }
    }
    return false;
}

int count_adjacent_bombs(int x, int y)
{
    int count = 0;
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if(dx == 0 && dy == 0) continue;
            
            int nx = x + dx;
            int ny = y + dy;
            
            if(nx >= 0 && nx < LENGTH && ny >= 0 && ny < LENGTH && is_bomb(nx, ny)){
                count++;
            }
        }
    }
    return count;
}

void display_bombs(void)
{
    for(int i = 0; i < NUMBER_OF_BOMB; ++i){
        board[bomb_coords[i].y][bomb_coords[i].x] = BOMB;
    }
}
