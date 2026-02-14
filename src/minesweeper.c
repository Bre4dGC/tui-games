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
bool open_cell(point pt);
bool do_action(void);
bool is_bomb(point pt);
int count_adjacent_bombs(point pt);
void display_bombs(void);

int main(void)
{
    srand(time(NULL));

    init();
    do draw(); while(!do_action());
    
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
        point pt;
        do {
            pt.x = rand() % LENGTH;
            pt.y = rand() % LENGTH;
        } while (is_bomb(pt));

        bomb_coords[i].x = pt.x;
        bomb_coords[i].y = pt.y;
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

bool open_cell(point pt)
{
    if(pt.x < 0 || pt.x >= LENGTH || pt.y < 0 || pt.y >= LENGTH) return false;
    if(board[pt.y][pt.x] != HIDDEN && board[pt.y][pt.x] != FLAGGED) return false;
    if(is_bomb(pt)) return true;
    
    int count = count_adjacent_bombs(pt);
    board[pt.y][pt.x] = count;

    if(count == 0){
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                open_cell((point){.x = pt.x + dx, .y = pt.y + dy});
            }
        }
    }

    return false;
}

bool do_action(void)
{
    switch(getch()){
        case 'w': MOVE_UP;    break;
        case 'a': MOVE_LEFT;  break;
        case 's': MOVE_DOWN;  break;
        case 'd': MOVE_RIGHT; break;
        case 'q': return true;
        case 'f':
            board[cursor.y][cursor.x] = board[cursor.y][cursor.x] == HIDDEN ? FLAGGED : HIDDEN;
            break;
        case ' ': 
            if(board[cursor.y][cursor.x] == HIDDEN){
                return open_cell(cursor);
            }
            break;
        default: break;
    }
    return false;
}

bool is_bomb(point pt)
{
    for(int i = 0; i < NUMBER_OF_BOMB; ++i){
        if(pt.x == bomb_coords[i].x && pt.y == bomb_coords[i].y){
            return true;
        }
    }
    return false;
}

int count_adjacent_bombs(point pt)
{
    int count = 0;
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if(dx == 0 && dy == 0) continue;
            
            point n = {.x = pt.x + dx, .y = pt.y + dy};
            
            if(n.x >= 0 && n.x < LENGTH && n.y >= 0 && n.y < LENGTH && is_bomb(n)){
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
