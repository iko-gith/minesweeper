#ifndef PLR_INPUT_H
#define PLR_INPUT_H

#include "../../constants.h"

enum {
    ACTION_INVALID = 0,
    ACTION_HELP    = 1,
    ACTION_REVEAL  = 2,
    ACTION_FLAG    = 3,
    ACTION_QUIT    = 4,
    ACTION_NEW_GAME= 5
};

void clear_input();
int get_plr_input(int *x, int *y);

#endif
