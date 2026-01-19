#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <threads.h>

#define BOARD_SIZE 10

#define CELL_CURRENT board[y][x]
#define CELL_ABOVE   board[y-1][x]
#define CELL_BOTTOM  board[y+1][x]
#define CELL_LEFT    board[y][x-1]
#define CELL_RIGHT   board[y][x+1]

#define MSLEEP(M) thrd_sleep(&(struct timespec){.tv_nsec = M * CLOCKS_PER_SEC}, NULL);
#define SSLEEP(S) thrd_sleep(&(struct timespec){.tv_sec = S}, NULL);

#define MOVE_UP     if(cursor.y > 0) cursor.y--
#define MOVE_LEFT   if(cursor.x > 0) cursor.x--
#define MOVE_DOWN   if(cursor.y < BOARD_SIZE-1) cursor.y++
#define MOVE_RIGHT  if(cursor.x < BOARD_SIZE-1) cursor.x++

typedef enum { RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GRAY } colors;
typedef struct {int y; int x;} point;

char* color_code(colors color)
{
    switch(color)
    {
        case RED:   return "\033[31m";
        case GREEN: return "\033[32m";
        case BLUE:  return "\033[34m";
        case YELLOW: return "\033[33m";
        case MAGENTA: return "\033[35m";
        case CYAN:  return "\033[36m";
        case GRAY:  return "\033[30m";
        default:    return "\033[30m";
    }
}

void put_colored(char ch, colors color)
{
    printf("%s%c\033[0m", color_code(color), ch);
    fflush(stdout);
}

void print_colored(const char *text, colors color) 
{
    if (color < RED || color > CYAN) {
        fprintf(stderr, "Invalid color\n");
        return;
    }

    printf("%s%s\033[0m\n", color_code(color), text);
}

char get_ch(void) {
    struct termios oldt, newt;
    char c;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    c = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return c;
}

#endif // UTILS_H
