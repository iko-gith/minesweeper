#ifndef RENDER_H
#define RENDER_H

#include "../board/board.h"
#include "../game/game.h"
#include "../../constants.h"

/*
 * @brief Функция для очистки экрана
 */

void clear_screen();

/*
 * @brief Функция для вывода ячейки поля игры
 * @define cell Структура с информацией ячейки
 */

void render_cell(const Cell *cell);

/*
 * @brief Функция для вывода доски игры
 * @define board Структура доски игры
 */

void render_board(const Board *board);

/*
 * @brief Функция для вывода верхушки игры
 * @define game Информация игры
 */

void render_header(const GameInfo *game);

/*
 * @brief Функция для вывода комманд
 */

void render_help_list();

/*
 * @brief Функция для вывода начальной информации игры
 * @define game Информация игры
 */

void render_welcome(const GameInfo *game);

/*
 * @brief Функция для вывода всей игры
 * @define game Информация игры
 */

void render_game(const GameInfo *game);

#endif
