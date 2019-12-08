#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const int GRID_SIZE = 4;
const int SHUFFLE_COUNT = 3;

bool win(int n, char grid[GRID_SIZE][GRID_SIZE]){
    int row, col;
    int v;
    if(grid[n-1][n-1] != 0){
        return false;
    }
    for(int i=0; i< n*n-1; i++){
        row = i / n;
        col = i % n;
        if(grid[row][col] != i+1){
            return false;
        }
    }
    return true;
}
bool move_up(int n, char grid[GRID_SIZE][GRID_SIZE]){
    int row, col;
    for(row = 0; row<n; row++){
        for(col=0; col<n; col++){
            if(grid[row][col] == 0){
                break;
            }
        }
        if(grid[row][col] == 0){
            break;
        }
    }
    if(row == 0)
        return false;
    grid[row][col] = grid[row-1][col];
    grid[row-1][col] = 0;

    return true;
}

bool move_down(int n, char grid[GRID_SIZE][GRID_SIZE]){
    int row, col;
    for(row = 0; row<n; row++){
        for(col=0; col<n; col++){
            if(grid[row][col] == 0){
                break;
            }
        }
        if(grid[row][col] == 0){
            break;
        }
    }
    if(row == n-1)
        return false;
    grid[row][col] = grid[row+1][col];
    grid[row+1][col] = 0;

    return true;
}

bool move_left(int n, char grid[GRID_SIZE][GRID_SIZE]){
    int row, col;
    for(row = 0; row<n; row++){
        for(col=0; col<n; col++){
            if(grid[row][col] == 0){
                break;
            }
        }
        if(grid[row][col] == 0){
            break;
        }
    }
    if(col == 0)
        return false;
    grid[row][col] = grid[row][col-1];
    grid[row][col-1] = 0;
    return true;
}
bool move_right(int n, char grid[GRID_SIZE][GRID_SIZE]){
    int row, col;
    for(row = 0; row<n; row++){
        for(col=0; col<n; col++){
            if(grid[row][col] == 0){
                break;
            }
        }
        if(grid[row][col] == 0){
            break;
        }
    }
    if(col == n-1)
        return false;
    grid[row][col] = grid[row][col+1];
    grid[row][col+1] = 0;

    return true;
}

void shuffle(int n, grid[GRID_SIZE][GRID_SIZE]){
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i < SHUFFLE_COUNT;){
        int d = rand() % n;
        switch (d){
        case 0:
            move_left(n, grid) && i++;
            break;
        case 1:
            move_up(n, grid) && i++;
            break;
        case 2:
            move_right(n, grid) && i++;
            break;
        case 3:
            move_down(n, grid) && i++;
            break;
        }
    }
}

void init_grid(int n, char grid[GRID_SIZE][GRID_SIZE]){
    for(int row = 0; row<n; row++){
        for(int col=0; col<n; col++){
            grid[row][col] = row * GRID_SIZE + col + 1;
        }
    }
    grid[n-1][n-1] = 0;
}

void print_grid(int n, char grid[GRID_SIZE][GRID_SIZE]){
    printf("\n+--+--+--+--+\n");
    for(int row = 0; row<n; row++){
        printf("|");
        for( int col=0 ; col<n; col++){
            if(grid[row][col] == 0){
                printf("  |");
            }
            else{
            printf("%02d|", grid[row][col]);
            }

        }
         printf("\n+--+--+--+--+\n");
    }
    printf("\n");
}

int main()
{
    system("clear");
    char grid[GRID_SIZE][GRID_SIZE];
    init_grid(GRID_SIZE, grid);
    shuffle(GRID_SIZE, grid);
    print_grid(GRID_SIZE, grid);
    for(bool exit = false; !exit;){
        char key = getchar();
        switch (key){
        case 'd':
            move_left(GRID_SIZE, grid);
            break;
        case 's':
            move_up(GRID_SIZE, grid);
            break;
        case 'a':
            move_right(GRID_SIZE, grid);
            break;
        case 'w':
            move_down(GRID_SIZE, grid);
            break;
        case 'e':
            exit = true;
            continue;
        default:
            continue;
        }
        system("clear");
        print_grid(GRID_SIZE, grid);
        if(win(GRID_SIZE, grid)){
            printf("Вы выиграли!\n");
            break;
        }
    }
    return 0;
}
