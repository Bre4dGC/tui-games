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

#define PRINT_S_RED(s)     printf("\033[31m%s\033[0m", s)
#define PRINT_S_GREEN(s)   printf("\033[32m%s\033[0m", s)
#define PRINT_S_BLUE(s)    printf("\033[34m%s\033[0m", s)
#define PRINT_S_YELLOW(s)  printf("\033[33m%s\033[0m", s)
#define PRINT_S_MAGENTA(s) printf("\033[35m%s\033[0m", s)
#define PRINT_S_CYAN(s)    printf("\033[36m%s\033[0m", s)
#define PRINT_S_GRAY(s)    printf("\033[30m%s\033[0m", s)

#define PRINT_C_RED(c)     printf("\033[31m %c \033[0m", c)
#define PRINT_C_GREEN(c)   printf("\033[32m %c \033[0m", c)
#define PRINT_C_BLUE(c)    printf("\033[34m %c \033[0m", c)
#define PRINT_C_YELLOW(c)  printf("\033[33m %c \033[0m", c)
#define PRINT_C_MAGENTA(c) printf("\033[35m %c \033[0m", c)
#define PRINT_C_CYAN(c)    printf("\033[36m %c \033[0m", c)
#define PRINT_C_GRAY(c)    printf("\033[30m %c \033[0m", c)

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

char getch(void)
{
    return _getch();
}

int is_key_pressed(void)
{
    
}
#endif

#ifdef __linux__
#include <termios.h>
#include <threads.h>
#include <fcntl.h>

#define MSLEEP(M) thrd_sleep(&(struct timespec){.tv_nsec = M * CLOCKS_PER_SEC}, NULL);
#define SSLEEP(S) thrd_sleep(&(struct timespec){.tv_sec = S}, NULL);

struct termios original_termios;

char getch(void)
{
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

void set_nonblock_mode(void)
{
    struct termios new_termios;

    tcgetattr(STDIN_FILENO, &original_termios);
    new_termios = original_termios;

    new_termios.c_lflag &= ~(ICANON | ECHO);

    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

char is_key_pressed(void)
{
    char ch;    
    if(read(STDIN_FILENO, &ch, 1) > 0) return ch;
    return 0;
}
#endif

#endif // UTILS_H
