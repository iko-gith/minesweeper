#include <time.h>
#include <stdlib.h>
#include "board.h"
#include "../output/output.h"

int out_of_bounds(Board *board, int x, int y) {
    return (x < 0 || x >=board->height || y < 0 || y >= board->width);
}

void free_board(Board *board) {
    if (board->cells) {
        for (int x = 0; x < board->height; x++)
            free(board->cells[x]);
        free(board->cells);
	board->cells = NULL;
    }
}

void update_board_size(Board *board, int height, int width) {
    if (height > 5 && width > 5) {
        board->height = height;
        board->width  = width;
    }
}

void init_board(Board *board) {
    write_to_file(OUTPUT_LOG, "\n> Initializing board:");
    
    // Очистка доски
    write_to_file(OUTPUT_LOG, "\nFreeing board memory");
    if (board->cells)
        free_board(board);

    if (!board->height || board->height < 5 || 
        !board->width  || board->width  < 5)
	return;
    
    // Выделение памяти доски
    write_to_file(OUTPUT_LOG, "\nAllocating board memory (%d %d)",
		  board->height, board->width);
    board->cells = (Cell **)malloc(board->height * sizeof(Cell *));
    for (int x = 0; x < board->height; x++)
        board->cells[x] = (Cell *)malloc(board->width * sizeof(Cell));

    // Выставляем начальные данные
    write_to_file(OUTPUT_LOG, "\nSetting default settings for cells");
    for (int x = 0; x < board->height; x++) {
        for (int y = 0; y < board->width; y++) {
	    board->cells[x][y].bombs_around = 0;
	    board->cells[x][y].has_bomb     = 0;
	    board->cells[x][y].state	    = CELL_HIDDEN;
	}
    }
    
    // Рандомный сид геренации
    time_t seed = time(NULL);
    write_to_file(OUTPUT_LOG, "\nSeed: %ld", seed);
    srand(seed);
    
    // Расставка бомб
    int bombs_placed = 0;
    while (bombs_placed < BOMBS_COUNT) {
        int x = rand() % board->height;
	int y = rand() % board->width;

	if (!board->cells[x][y].has_bomb) {
	     board->cells[x][y].has_bomb = 1;
	     bombs_placed               += 1;
	}
    }
    write_to_file(OUTPUT_LOG, "\nBombs placed in random positions, total: %d",
		              bombs_placed);

    // Вычисление близлежащих бомб, 8 клеток вокруг позиции проверки
    for (int x = 0; x < board->height; x++) {
        for (int y = 0; y < board->width; y++) {
	    if (!board->cells[x][y].has_bomb) {
	        int bomb_count = 0;

		// Начало подсчёта близлежащих клеток
		for (int dx = -1; dx <= 1; dx++) {
		    for (int dy = -1; dy <= 1; dy++) {
		        // Проверяем, что данные не равны 0(Позиция проверки)
			if (dx || dy) {
			    int check_x = x+dx;
			    int check_y = y+dy;
			    
			    // Проверка на выход за границы и наличие бомбы
			    if (!out_of_bounds(board, check_x, check_y) && 
			        board->cells[check_x][check_y].has_bomb)
				    bomb_count += 1;
			    
			}
		    }
		}

		board->cells[x][y].bombs_around = bomb_count;
	    }
	}
    }

    write_to_file(OUTPUT_LOG, "\nCompleted initializing board");
};

void reveal_cell(Board *board, int x, int y) {
    // Проверка на выход за границы
    if (out_of_bounds(board, x, y) || !board->cells)
	return;
    
    // Проверка на статус (Должно быть не раскрытым)
    if (board->cells[x][y].state != CELL_HIDDEN)
	return;
    
    // Меняем статус на показан
    board->cells[x][y].state = CELL_SHOWN;
    
    // Если не бомба и рядом нету бомб, раскрываем близ-лежащие клетки
    if (!board->cells[x][y].has_bomb && !board->cells[x][y].bombs_around) {
        for (int dx = -1; dx <= 1; dx++) {
	    for (int dy = -1; dy <= 1; dy++) {
	        if (dx || dy)
		    reveal_cell(board, x+dx, y+dy);
	    }
	}
    }
}

void reveal_all_cells(Board *board) {
    if (!board->cells)
	return;

    write_to_file(OUTPUT_LOG, "\n> Revealing all cells");

    for (int x = 0; x < board->height; x++) {
        for (int y = 0; y < board->width; y++) {
	    board->cells[x][y].state = CELL_SHOWN;
	}
    }
}

void toggle_flag(Board *board, int x, int y) {
    if (out_of_bounds(board, x, y) || !board->cells)
	return;

    switch(board->cells[x][y].state) {
        case CELL_HIDDEN:
            write_to_file(OUTPUT_LOG, "\n> Flagged cell (%d %d)", x, y);
	    board->cells[x][y].state = CELL_FLAGGED;
	    break;

	case CELL_FLAGGED:
	    write_to_file(OUTPUT_LOG, "\n> Unflagged cell (%d %d)", x, y);
	    board->cells[x][y].state = CELL_HIDDEN;
	    break;
    }
}

int is_game_lost(Board *board) {
    if (!board->cells)
	return 0;

    for (int x = 0; x < board->height; x++) {
        for (int y = 0; y < board->width; y++) {
            int has_bomb   = board->cells[x][y].has_bomb;
            int cell_state = board->cells[x][y].state;

            // Проверка - клетка с бомбой и показана
            if (has_bomb && cell_state == CELL_SHOWN) 
                return 1;
        }
    }

    return 0;
}

int is_game_won(Board *board) {
    if (!board->cells)
	return 0;
	
    for (int x = 0; x < board->height; x++) {
        for (int y = 0; y < board->width; y++) {
            int has_bomb   = board->cells[x][y].has_bomb;
            int cell_state = board->cells[x][y].state;

            // Проверка - клетка без бомбы и не показана
            if (!has_bomb && cell_state != CELL_SHOWN)
                return 0;

            // Проверка - клетка без бомбы и помечена флагом
            if (!has_bomb && cell_state == CELL_FLAGGED)
                return 0;
        }
    }

    return 1;
}

int count_flagged_bombs(Board *board) {
    int flagged = 0;
    if (!board->cells)
	return flagged;

    for (int x = 0; x < board->height; x++) {
        for (int y = 0; y < board->width; y++) {
            int cell_state = board->cells[x][y].state;
	    
	    if (cell_state == CELL_FLAGGED)
		flagged += 1;
	}
    }

    return flagged;
}
