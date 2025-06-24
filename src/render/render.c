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
    int height = board->height;
    int width  = board->width;

    printf("\n   ");
    for (int x = 0; x < height; x++)
        printf("%2d%s", x, (x+1>=height) ? "\n" : "");

    printf("   +");
    for (int x = 0; x < height; x++)
	printf("--%s", (x+1>=height) ? "+\n" : "");

    for (int x = 0; x < height; x++) {
	printf("%2d |", x);
        for (int y = 0; y < width; y++) {
	    render_cell(&board->cells[x][y]);
	}

	printf("|\n");
    }

    printf("   +");
    for (int x = 0; x < height; x++)
        printf("--%s", (x+1>=height) ? "+\n" : "");
}

void render_header(const GameInfo *game) {
    printf("===Minesweeper===\n"
           "Total bombs: %d\n", game->bombs);
    
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
	default:
	    printf("NaN\n");
	    break;
    }
}

void render_help_list() {
    printf("List of commands:\n"
           "H - List of commands\n"
	   "R (number) (number) - Reveal cell using coordinates\n"
	   "F (number) (number) - Flag cell using coordinates\n"
	   "Q - Quit the game\n"
	   "N - Start new game\n"
	   "S (number) (number) - Change board height and width\n"
	   "B (number) - Set amount of bombs");
}

void render_error() {
    printf("Invalid command.\n");
}

void render_welcome(const GameInfo *game) {
    printf("===Minesweeper===\n"
	   "To start the game use following commands:\n");
    if (!game->bombs)
	printf("B (number) - Set amount of bombs\n");

    if (!game->board.height || !game->board.width)
	printf("S (number) (number) - Set board height and width\n");

    printf("Type H for more commands.\n");
}

void render_game(const GameInfo *game) {
    clear_screen();
    if (game->state != GAME_NOT_INIT) {
        render_header(game);
        render_board(&game->board);
    } else {
        render_welcome(game);
    }
}
