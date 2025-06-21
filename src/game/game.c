#include "game.h"
#include "../output/output.h"

void init_game(GameInfo* game) {
    // Инициализация поля
    init_board(&game->board);
    
    // Инициализация данных игры
    game->state      = GAME_PROC;
    game->mines_left = BOMBS_COUNT;
}

void update_game(GameInfo* game) {
    // Обновление и проверка статуса игры
    write_to_file(OUTPUT_LOG, "\n> Game status: ");

    if (is_game_lost(&game->board)) {
        write_to_file(OUTPUT_LOG, "Lost");
	reveal_all_cells(&game->board);
	game->state = GAME_LOST;
    }
    else if (is_game_won(&game->board)) {
	write_to_file(OUTPUT_LOG, "Won");
        game->state = GAME_WON;
    } else {
	write_to_file(OUTPUT_LOG, "In process");
	game->mines_left = count_bombs_left(&game->board);
        game->state = GAME_PROC;
    }
}


