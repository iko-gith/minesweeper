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
    int bombs;
} GameInfo;

/*
 * @brief Функция для изменения количества бомб игры
 * @define game       Информация игры
 * @define bomb_count Количество бомб
 */

void update_bomb_count(GameInfo *game, int bomb_count);

/*
 * @brief Функция для инициализации игры
 * @define game       Информация игры
 */

void init_game(GameInfo* game);

/*
 * @brief Функция для обновления статуса игры
 * @define game       Информация игры
 */

void update_game(GameInfo* game);

#endif
