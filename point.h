#ifndef POINT_H
#define POINT_H

/**
 * @brief Структура, хранящая положение фигуры на доске
 * 
 */
struct Point
{
    short x; ///< Хранит координату x - по горизонтали
    short y; ///< Хранит координату y - по вертикали

    /**
     * @brief Конструктор класса по умолчанию Point
     * 
     */
    Point(): x(0), y(0) {}

    /**
     * @brief Конструктор класса Point
     * 
     * @param _x Координата x
     * @param _y Координата y
     */
    Point(short _x, short _y): x(_x), y(_y) {}

    /**
     * @brief Оператор сравнения двух положения
     * 
     * @param other Ячейка, с которой нужно сравнить
     * @return true Возвращаемое значения, если позиции одинаковы
     * @return false Возвращаемое значения, если позиции различны
     */
    bool operator==(Point other)
    {
        return (other.x == x) && (other.y == y);
    }
};

#endif