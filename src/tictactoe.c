#include "utils.h"

#define FIELD_SIZE 3

char field[FIELD_SIZE][FIELD_SIZE] = {"   ", "   ", "   "};
point cursor = {0,0};

void draw(void);
bool win_check(void);
bool move(const char player);

int main(void)
{
    char player = 'X';
    bool correct = false;
    while(true){
        draw();

        printf("Turn player %c\n", player);
        switch(get_ch()){
            case 'w': MOVE_UP;    continue;
            case 'a': MOVE_LEFT;  continue;
            case 's': MOVE_DOWN;  continue;
            case 'd': MOVE_RIGHT; continue;
            case ' ': correct = move(player); break;
            case 'q': return 0;
        }
        
        if(win_check()) break;
        if(correct) player = player == 'X' ? 'O' : 'X';
    }
    return 0;
}

void draw(void)
{
    puts("");
    for(int i = 0; i < FIELD_SIZE; ++i){
        for(int j = 0; j < FIELD_SIZE; ++j){
            if(cursor.y == i && cursor.x == j){
                printf("[%c]", field[i][j]);
            }
            else {
                printf(" %c ", field[i][j]);
            }
            if(j < FIELD_SIZE - 1) printf("|");
        }
        if(i < FIELD_SIZE - 1) printf("\n---+---+---\n");
    }
    puts("");
}

bool win_check(void)
{
    for(int i = 0; i < FIELD_SIZE; i++){
        if((field[i][0] == field[i][1] && field[i][1] == field[i][2] && field[i][0] != ' ') ||
           (field[0][i] == field[1][i] && field[1][i] == field[2][i] && field[0][i] != ' ')){
            printf("\nPlayer %c win!", field[i][i]);
            goto win;
        }
    }
    if((field[0][0] == field[1][1] && field[1][1] == field[2][2] && field[0][0] != ' ') || 
       (field[0][2] == field[1][1] && field[1][1] == field[2][0] && field[0][2] != ' ')){
        printf("\nPlayer %c win!", field[1][1]);
        goto win;
    }

    bool is_draw = true;
    
    for(int i = 0; i < FIELD_SIZE; i++){
        for(int j = 0; j < FIELD_SIZE; j++){
            if(field[i][j] == ' '){
                is_draw = false;
                break;
            }
        }
        if(!is_draw) break;
    }
    if(is_draw){
        printf("\nDraw!");
        goto win;
    }
    return false;

win:
    draw();
    return true;
}

bool move(const char player)
{
    if(cursor.x >= 0 && cursor.x <= FIELD_SIZE && cursor.y >= 0 && cursor.y <= FIELD_SIZE){
        if(field[cursor.y][cursor.x] != 'X' && field[cursor.y][cursor.x] != 'O'){
            field[cursor.y][cursor.x] = player;
            return true;
        }
    }
    return false;
}
