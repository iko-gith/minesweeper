#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "output.h"

/*
 * @brief  Функция позволяет записывать какие либо строки в файл
 * @define filename Путь до файла, в который будет записана информация
 * @define format   Строка, которая будет записана в заданный файл
 * @return result   Успешная\Неуспешная запись в файл
 */

int write_to_file(const char* filename, const char* format, ...) {
    int result = 0;
    FILE *file = fopen(filename, "a");

    if (file) {
        va_list args;
        va_start(args, format);
        vfprintf(file, format, args);
        va_end(args);
    
        fclose(file);
	result = 1;
    }

    return result;
}
