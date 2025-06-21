#include "src/game/game.h"
#include "src/plr_input/plr_input.h"
#include "src/render/render.h"
#include "src/output/output.h"

static void new_game(GameInfo *game) {
    init_game(game);
    render_game(game);
}

int main() {
    int playing = 1;

    GameInfo game;
    new_game(&game);

    while (playing) {
        int x, y;
	int plr_action = get_plr_input(&x, &y);
        
        write_to_file(OUTPUT_LOG, "\n> Player input: ");
        
	switch(plr_action) {
	    case ACTION_HELP:
		write_to_file(OUTPUT_LOG, "Help");
		// Помощь!!!
		break;
	    case ACTION_NEW_GAME:
		write_to_file(OUTPUT_LOG, "New Game");
		new_game(&game);
	    case ACTION_REVEAL:
		write_to_file(OUTPUT_LOG, "Reveal (%d %d)", x, y);
		reveal_cell(&game.board, x, y);
		break;
	    case ACTION_FLAG:
		write_to_file(OUTPUT_LOG, "Flag (%d %d)", x, y);
		toggle_flag(&game.board, x, y);
		break;
	    case ACTION_QUIT:
		write_to_file(OUTPUT_LOG, "Quit");
		playing = 0;
		break;
	    default:
		write_to_file(OUTPUT_LOG, "Invalid");
	        break;
	}
	
	if (playing) {
            update_game(&game);
            render_game(&game);
	}
    }

    return 0;
}
