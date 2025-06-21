#ifndef GAME_H
#define GAME_H

#include "../board/board.h"
#include "../../constants.h"

enum {
    GAME_NOT_INIT = -1,
    GAME_PROC	  = 0,
    GAME_WON	  = 1,
    GAME_LOST     = 2
};

typedef struct {
    Board board;
    int state;
    int mines_left;
} GameInfo;

void init_game(GameInfo* game);
void update_game(GameInfo* game);

#endif
