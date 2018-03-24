#ifndef POINT_H
#define POINT_H

/**
 * @brief Структура, хранящая положение фигуры на доске
 * 
 */
struct Point
{
    unsigned short x; ///< Хранит координату x - по горизонтали
    unsigned short y; ///< Хранит координату y - по вертикали

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