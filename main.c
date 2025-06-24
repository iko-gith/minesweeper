#include <stddef.h>
#include "src/game/game.h"
#include "src/plr_input/plr_input.h"
#include "src/render/render.h"
#include "src/output/output.h"

void new_game(GameInfo *game) {
    init_game(game);
    render_game(game);
}

void update(GameInfo *game) {
    update_game(game);
    render_game(game);
}

int main() {
    int playing = 1;

    GameInfo game;
    game.state        = GAME_NOT_INIT;
    game.bombs        = 0;
    game.board.cells  = NULL;
    game.board.height = 0;
    game.board.width  = 0;
    
    clear_screen();
    render_welcome(&game);
    while (playing) {
        int x, y;
	int plr_action = get_plr_input(&x, &y);
        
        write_to_file(OUTPUT_LOG, "\n> Player input: ");
        
	switch(plr_action) {
	    case ACTION_HELP:        // Помощь
		write_to_file(OUTPUT_LOG, "Help");
		render_help_list();
		break;

	    case ACTION_NEW_GAME:    // Новая игра
		write_to_file(OUTPUT_LOG, "New Game");
		new_game(&game);
		break;

	    case ACTION_REVEAL:      // Раскрыть клетку
		write_to_file(OUTPUT_LOG, "Reveal (%d %d)", x, y);
		reveal_cell(&game.board, x, y);
		update(&game);
		break;

	    case ACTION_FLAG:	     //Поставить флажок
		write_to_file(OUTPUT_LOG, "Flag (%d %d)", x, y);
		toggle_flag(&game.board, x, y);
		update(&game);
		break;

	    case ACTION_QUIT:	     // Выйти из игры
		write_to_file(OUTPUT_LOG, "Quit");
		playing = 0;
		clear_screen();
		break;

            case ACTION_CHANGE_BOARD:// Поменять размер поля
		write_to_file(OUTPUT_LOG, "New board size (%d %d)", x, y);
		update_board_size(&game.board, x, y);
		new_game(&game);
		break;

	    case ACTION_CHANGE_BOMBS:// Поменять количество бомб
		write_to_file(OUTPUT_LOG, "Change bombs (%d)", x);
		update_bomb_count(&game, x);
		new_game(&game);
		break;

	    default:
		write_to_file(OUTPUT_LOG, "Invalid");
	        render_error();
		break;

	}
    }
    
    free_board(&game.board);
    return 0;
}
