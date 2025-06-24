#ifndef BOARD_H
#define BOARD_H

#define BOMBS_COUNT 20

#include "../../constants.h"

enum {
    CELL_HIDDEN  = 0,
    CELL_SHOWN   = 1,
    CELL_FLAGGED = 2
};

typedef struct {
    int state;
    int bombs_around;
    int has_bomb;
} Cell;

typedef struct {
    Cell **cells;
    int height;
    int width;
} Board;

/*
 * @brief Функция для определения выхода координат за границы поля
 * @define board Доска игры
 * @define x Координата по оси x
 * @define y Координата по оси y
 * @return Цифра 1 (Если выходит) 0 (Если в границах)
 */

int out_of_bounds(Board *board, int x, int y);

/*
 * @brief Функция для высвобождение памяти доски
 * @define board Доска игры с выделенной памятью
 */

void free_board(Board *board);

/*
 * @brief Функция для обновление размеров доски
 * @define height Высота доски по оси x
 * @define width Ширина доски по оси y
 */

void update_board_size(Board *board, int height, int width);

/*
 * @brief Функция для инициализации доски, выставления бомб и выделения памяти
 * @define board Доска игры
 * @define bomb_count Количество бомб, которое будет установленно на поле
 */

void init_board(Board *board, int bomb_count);

/*
 * @brief Функция для раскрытия клетки поля
 * @define board Доска игры
 * @define x     Координата по оси x
 * @define y     Координата по оси y
 */

void reveal_cell(Board *board, int x, int y);

/*
 * @brief Функция для раскрытия всех клеток поля
 * @define board Доска игры
 */

void reveal_all_cells(Board *board);

/*
 * @brief Функция, позволяющая поставить\удалить флажок на поле
 * @define x     Координата по оси x
 * @define y     Координата по оси y
 */

void toggle_flag(Board* board, int x, int y);

/*
 * @brief Функция для проверки на проигрыш игры
 * @define board Доска игры
 */

int is_game_lost(Board *board);

/*
 * @brief Функция для проверки на выйгрыш игры
 * @define board Доска игры
 */

int is_game_won(Board *board);

/*
 * @brief Функция для посчета количества помеченных флажком бомб
 * @define board Доска игры
 */

int count_flagged_bombs(Board *board);

#endif
