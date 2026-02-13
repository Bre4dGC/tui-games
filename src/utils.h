#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 10

#define CELL_CURRENT board[y][x]
#define CELL_ABOVE   board[y-1][x]
#define CELL_BOTTOM  board[y+1][x]
#define CELL_LEFT    board[y][x-1]
#define CELL_RIGHT   board[y][x+1]

#define MOVE_UP     if(cursor.y > 0) cursor.y--
#define MOVE_LEFT   if(cursor.x > 0) cursor.x--
#define MOVE_DOWN   if(cursor.y < BOARD_SIZE-1) cursor.y++
#define MOVE_RIGHT  if(cursor.x < BOARD_SIZE-1) cursor.x++

#define POINT_CMP(a,b) (a.x == b.x && a.y == b.y)

#define PRINT_RED(s)     printf("\033[31m%s\033[0m", s)
#define PRINT_GREEN(s)   printf("\033[32m%s\033[0m", s)
#define PRINT_BLUE(s)    printf("\033[34m%s\033[0m", s)
#define PRINT_YELLOW(s)  printf("\033[33m%s\033[0m", s)
#define PRINT_MAGENTA(s) printf("\033[35m%s\033[0m", s)
#define PRINT_CYAN(s)    printf("\033[36m%s\033[0m", s)
#define PRINT_GRAY(s)    printf("\033[30m%s\033[0m", s)

#define IS_KEY_PRESSED (true)

typedef enum {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, GRAY} colors;
typedef enum {UP, DOWN, LEFT, RIGHT} direction;
typedef struct {int y; int x;} point;

char* color_code(colors color)
{
    switch(color)
    {
        case RED:     return "\033[31m";
        case GREEN:   return "\033[32m";
        case BLUE:    return "\033[34m";
        case YELLOW:  return "\033[33m";
        case MAGENTA: return "\033[35m";
        case CYAN:    return "\033[36m";
        case GRAY:    return "\033[30m";
        default:      return "\033[30m";
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

// support for windows and linux
#ifdef _WIN32
#include <conio.h>
#include <windows.h>

#define MSLEEP(M) Sleep(M)
#define SSLEEP(S) Sleep(S * 1000)

char get_ch(void) {
    return _getch();
}
#endif

#ifdef __linux__
#include <termios.h>
#include <threads.h>

#define MSLEEP(M) thrd_sleep(&(struct timespec){.tv_nsec = M * CLOCKS_PER_SEC}, NULL);
#define SSLEEP(S) thrd_sleep(&(struct timespec){.tv_sec = S}, NULL);

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
#endif

#endif // UTILS_H
