#include <stdio.h>
#include <stdlib.h>

#include "render.h"

void clear_screen() {
    system("clear");
}

void render_cell(const Cell *cell) {
    if (cell->state == CELL_HIDDEN) {
        printf("■ ");
    }
    else if (cell->state == CELL_FLAGGED) {
        printf("⚑ ");
    }
    else {
	if (cell->has_bomb) {
            printf("☼ ");
	}
	else {
	    printf("%d ", cell->bombs_around);
	}
    }
}

void render_board(const Board *board) {
    printf("\n   ");
    for (int x = 0; x < BOARD_SIZE; x++)
        printf("%2d%s", x, (x+1>=BOARD_SIZE) ? "\n" : "");

    printf("   +");
    for (int x = 0; x < BOARD_SIZE; x++)
	printf("--%s", (x+1>=BOARD_SIZE) ? "+\n" : "");

    for (int x = 0; x < BOARD_SIZE; x++) {
	printf("%2d |", x);
        for (int y = 0; y < BOARD_SIZE; y++) {
	    render_cell(&board->cells[x][y]);
	}

	printf("|\n");
    }

    printf("   +");
    for (int x = 0; x < BOARD_SIZE; x++)
        printf("--%s", (x+1>=BOARD_SIZE) ? "+\n" : "");
}

void render_header(const GameInfo *game) {
    printf("===Minesweeper===\n"
           "Flags: %d\n", game->mines_left);
    
    printf("Game State: ");
    switch(game->state) {
        case GAME_PROC:
	    printf("In Process\n");
	    break;
	case GAME_WON:
	    printf("Won\n");
	    break;
	case GAME_LOST:
	    printf("Lost\n");
	    break;
	case GAME_NOT_INIT:
	    printf("Not initialized\n");
	    break;
    }
    
}

void render_game(const GameInfo *game) {
    clear_screen();
    render_header(game);
    render_board(&game->board);
}
