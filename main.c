#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

typedef char byte;

#define BOARD_SIZE 4
#define SHUFFLE_COUNT 5

typedef struct
{
    byte board[BOARD_SIZE][BOARD_SIZE]; // Игровая доска
    byte row;                           // Номер строки с пустой клеткой
    byte col;                           // Номер стоолбца с пустой клеткой
    unsigned int moves;                 // Количество шагов
} game_state;

bool move_up(game_state *gs)
{
    if (gs->row == 0)
        return false;
    gs->board[gs->row][gs->col] = gs->board[gs->row - 1][gs->col];
    gs->board[gs->row - 1][gs->col] = 0;
    gs->moves++;
    gs->row--;
    return true;
}

bool move_down(game_state *gs)
{
    if (gs->row == BOARD_SIZE - 1)
        return false;
    gs->board[gs->row][gs->col] = gs->board[gs->row + 1][gs->col];
    gs->board[gs->row + 1][gs->col] = 0;
    gs->moves++;
    gs->row++;
    return true;
}

bool move_left(game_state *gs)
{
    if (gs->col == 0)
        return false;
    gs->board[gs->row][gs->col] = gs->board[gs->row][gs->col - 1];
    gs->board[gs->row][gs->col - 1] = 0;
    gs->moves++;
    gs->col--;
    return true;
}

bool move_right(game_state *gs)
{
    if (gs->col == BOARD_SIZE - 1)
        return false;
    gs->board[gs->row][gs->col] = gs->board[gs->row][gs->col + 1];
    gs->board[gs->row][gs->col + 1] = 0;
    gs->moves++;
    gs->col++;
    return true;
}

void shuffle_board(game_state *gs)
{
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < SHUFFLE_COUNT;)
    {
        int d = rand() % BOARD_SIZE;
        switch (d)
        {
        case 0:
            move_left(gs) && i++;
            break;
        case 1:
            move_up(gs) && i++;
            break;
        case 2:
            move_right(gs) && i++;
            break;
        case 3:
            move_down(gs) && i++;
            break;
        }
    }
}

game_state new_game()
{
    game_state gs;
    for (byte row = 0; row < BOARD_SIZE; row++)
    {
        for (byte col = 0; col < BOARD_SIZE; col++)
        {
            gs.board[row][col] = row * BOARD_SIZE + col + 1;
        }
    }
    gs.board[BOARD_SIZE - 1][BOARD_SIZE - 1] = 0;
    gs.row = BOARD_SIZE - 1;
    gs.col = BOARD_SIZE - 1;
    shuffle_board(&gs);
    gs.moves = 0;
    return gs;
}

bool check_win(game_state *gs)
{
    if (gs->col != BOARD_SIZE - 1 && gs->row != BOARD_SIZE - 1)
    {
        return false;
    }
    int row, col;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE - 1; i++)
    {
        row = i / BOARD_SIZE;
        col = i % BOARD_SIZE;
        if (gs->board[row][col] != i + 1)
        {
            return false;
        }
    }
    return true;
}

void print_game(game_state *gs)
{
    system("clear");
    printf("Куросвая работа игра \"Пятнашки\". Панько Д.А.\n");
    printf("--------------------------------------------\n");
    printf("Подсказка:\n");
    printf("    WASD - управление\n");
    printf("    N - начать заново\n");
    printf("    E - выход\n");
    printf("--------------------------------------------\n");
    printf("\n+--+--+--+--+\n");
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        printf("|");
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (gs->board[row][col] == 0)
            {
                printf("  |");
            }
            else
            {
                printf("%02d|", gs->board[row][col]);
            }
        }
        printf("\n+--+--+--+--+\n");
    }
    printf("\n");
    printf("Количество шагов:  %d\n", gs->moves);
}

int main()
{
    bool play = true;
    game_state gs = new_game();

    do
    {
        print_game(&gs);
        printf("Ввведите команду:\n");
        int key = tolower(getchar());
        switch (key)
        {
        case 'd':
            move_left(&gs);
            break;
        case 's':
            move_up(&gs);
            break;
        case 'a':
            move_right(&gs);
            break;
        case 'w':
            move_down(&gs);
            break;
        case 'n':
            gs = new_game();
            break;
        case 'e':
            play = false;
            continue;
        default:
            continue;
        }
        if (check_win(&gs))
        {
            print_game(&gs);
            printf("Вы выиграли!\n");
            break;
        }
    } while (play);

    return true;
}
