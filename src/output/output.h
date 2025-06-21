#ifndef OUTPUT_H
#define OUTPUT_H

/*
 * @brief  Функция позволяет записывать какие либо строки в файл
 * @define filename Путь до файла, в который будет записана информация
 * @define format   Строка, которая будет записана в заданный файл
 * @return result   Успешная\Неуспешная запись в файл
 */

int write_to_file(const char *filename, const char *format, ...);

#endif  // OUTPUT_H
