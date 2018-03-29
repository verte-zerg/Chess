#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "board.h"

class Board;

/**
 * @class Figure
 * @brief Шахматная фигура
 */
class Figure {
public:     
    Point pos; ///< Позиция фигуры
    FigureColor color; ///< Цвет фигуры

    /**
     * @brief Возвращает список возможных ходов
     * 
     * @param b Доска, на которой производится проверка
     * @return std::vector<Move> Список возможных ходов
     */
    virtual std::vector<Move> getMoves(Board* b) const = 0;  

    /**
     * @brief Конструктор по умолчанию
     * 
     * @param _pos Позиция фигуры
     * @param _color Цвет фигуры
     */
    Figure(Point _pos, FigureColor _color): pos(_pos), color(_color) {};   

    /**
     * @brief Конструктор копирования
     * 
     * @return Figure* Копия фигуры
     */
    virtual Figure* copy() const = 0;
};

#endif