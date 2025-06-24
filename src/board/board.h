#ifndef BOARD_H
#define BOARD_H

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
    Cell **cells;
    int height;
    int width;
} Board;

int out_of_bounds(Board *board, int x, int y);
void free_board(Board *board);
void update_board_size(Board *board, int height, int width);
void init_board(Board *board);
void reveal_cell(Board *board, int x, int y);
void reveal_all_cells(Board *board);
void toggle_flag(Board* board, int x, int y);
int is_game_lost(Board *board);
int is_game_won(Board *board);
int count_flagged_bombs(Board *board);

#endif
