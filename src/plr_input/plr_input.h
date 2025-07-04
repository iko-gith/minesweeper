#ifndef PLR_INPUT_H
#define PLR_INPUT_H

#include "../../constants.h"

enum {
    ACTION_INVALID      = 0,
    ACTION_HELP         = 1,
    ACTION_REVEAL       = 2,
    ACTION_FLAG         = 3,
    ACTION_QUIT         = 4,
    ACTION_NEW_GAME     = 5,
    ACTION_CHANGE_BOARD = 6,
    ACTION_CHANGE_BOMBS = 7
};

void clear_input();
int get_plr_input(int *x, int *y);

#endif
