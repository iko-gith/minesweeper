#ifndef RENDER_H
#define RENDER_H

#include "../board/board.h"
#include "../game/game.h"
#include "../../constants.h"

void clear_screen();
void render_cell(const Cell *cell);
void render_board(const Board *board);
void render_header(const GameInfo *game);
void render_game(const GameInfo *game);

#endif
