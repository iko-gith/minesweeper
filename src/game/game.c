#include "game.h"
#include "../output/output.h"

void init_game(GameInfo* game) {
    // Инициализация поля
    if (game->bombs)
	init_board(&game->board, game->bombs);
    
    // Инициализация данных игры
    if (!game->board.cells) {
        game->state      = GAME_NOT_INIT;
    } else {
        game->state      = GAME_PROC;
    }
}

void update_game(GameInfo* game) {
    // Обновление и проверка статуса игры
    write_to_file(OUTPUT_LOG, "\n> Game status: ");
    
    if (game->state == GAME_NOT_INIT) {
        write_to_file(OUTPUT_LOG, "Not initialized");
    }
    else if (is_game_lost(&game->board)) {
        write_to_file(OUTPUT_LOG, "Lost");
	reveal_all_cells(&game->board);
	game->state = GAME_LOST;
    }
    else if (is_game_won(&game->board)) {
	write_to_file(OUTPUT_LOG, "Won");
        game->state = GAME_WON;
    } else {
	write_to_file(OUTPUT_LOG, "In process");
        game->state = GAME_PROC;
    }
}

void update_bomb_count(GameInfo *game, int bomb_count) {
    if (!bomb_count || bomb_count <= 0)
	bomb_count = 1;
    
    game->bombs = bomb_count;
}
