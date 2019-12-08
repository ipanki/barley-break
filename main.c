#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const int BOARD_SIZE = 4;
const int SHUFFLE_COUNT = 3;

typedef struct
{
    uint8_t row;                     // Номер строки с пустой клеткой
    uint8_t col;                     // Номер стоолбца с пустой клеткой
    char board[BOARD_SIZE][BOARD_SIZE]; // Игровая доска
    uint32_t moves;                  // Количество шагов
} game_state;

bool move_up(game_state *gs){
    if(gs->row == 0)
        return false;
    gs->board[gs->row][gs->col] = gs->board[gs->row-1][gs->col];
    gs->board[gs->row-1][gs->col] = 0;
    gs->moves++;
    gs->row--;
    return true;
}

bool move_down(game_state *gs){
    if(gs->row == BOARD_SIZE -1)
        return false;
    gs->board[gs->row][gs->col] = gs->board[gs->row+1][gs->col];
    gs->board[gs->row+1][gs->col] = 0;
    gs->moves++;
    gs->row++;
    return true;
}

bool move_left(game_state *gs){
    if(gs->col == 0)
        return false;
    gs->board[gs->row][gs->col] = gs->board[gs->row][gs->col-1];
    gs->board[gs->row][gs->col-1] = 0;
    gs->moves++;
    gs->col--;
    return true;
}

bool move_right(game_state *gs){
    if(gs->col == BOARD_SIZE -1)
        return false;
    gs->board[gs->row][gs->col] = gs->board[gs->row][gs->col+1];
    gs->board[gs->row][gs->col+1] = 0;
    gs->moves++;
    gs->col++;
    return true;
}

void shuffle_board(game_state *gs){
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i < SHUFFLE_COUNT;){
        int d = rand() % BOARD_SIZE;
        switch (d){
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

game_state new_game(){
    game_state gs;
    for(int row = 0; row < BOARD_SIZE; row++){
        for(int col = 0; col < BOARD_SIZE; col++){
            gs.board[row][col] = row * BOARD_SIZE + col + 1;
        }
    }
    gs.board[BOARD_SIZE - 1][BOARD_SIZE - 1] = 0;
    gs.row = BOARD_SIZE - 1;
    gs.col = BOARD_SIZE - 1;
    gs.moves = 0;
    shuffle_board(&gs);
    return gs;
}

bool win(game_state *gs){
    if(gs->col != BOARD_SIZE - 1 && gs->row != BOARD_SIZE - 1){
        return false;
    }
    int row, col;
    for(int i=0; i< BOARD_SIZE * BOARD_SIZE - 1; i++){
        row = i / BOARD_SIZE;
        col = i % BOARD_SIZE;
        if(gs->board[row][col] != i + 1){
            return false;
        }
    }
    return true;
}


void print_board(game_state *gs){
    printf("\n+--+--+--+--+\n");
    for(int row = 0; row < BOARD_SIZE; row++){
        printf("|");
        for( int col = 0 ; col < BOARD_SIZE; col++){
            if(gs->board[row][col] == 0){
                printf("  |");
            }
            else{
            printf("%02d|", gs->board[row][col]);
            }

        }
         printf("\n+--+--+--+--+\n");
    }
    printf("\n");
}

int main()
{
    system("clear");

    game_state gs = new_game();

    for(bool exit = false; !exit;){
        system("clear");
        print_board(&gs);
        char key = getchar();
        switch (key){
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
        case 'e':
            exit = true;
            continue;
        default:
            continue;
        }
        if(win(&gs)){
            printf("Вы выиграли!\n");
            break;
        }
    }
    return 0;
}
