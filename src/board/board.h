#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 10
#define BOMBS_COUNT 20

#include "../../constants.h"

enum {
    CELL_HIDDEN  = 0,
    CELL_SHOWN   = 1,
    CELL_FLAGGED = 2
};

typedef struct {
    int state;
    int bombs_around;
    int has_bomb;
} Cell;

typedef struct {
    Cell cells[BOARD_SIZE][BOARD_SIZE];
} Board;

int out_of_bounds(int x, int y);
void init_board(Board *board);
void reveal_cell(Board *board, int x, int y);
void reveal_all_cells(Board *board);
void toggle_flag(Board* board, int x, int y);
int is_game_lost(Board *board);
int is_game_won(Board *board);
int count_bombs_left(Board *board);

#endif
