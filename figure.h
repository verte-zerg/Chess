#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "board.h"
#include "role.h"

class Board;

/**
 * @class Figure
 * @brief Шахматная фигура
 */
class Figure {
public:     
    Point pos; ///< Позиция фигуры
    FigureColor color; ///< Цвет фигуры
    const FigureName name; ///< Тип фигуры
    const double costControlCell; ///< Коэффициент оценки контролируемости ячеек

    /**
     * @brief Возвращает список возможных ходов
     * 
     * @param b Доска, на которой производится проверка
     * @return std::vector<Move> Список возможных ходов
     */
    virtual std::vector<Move> getMoves(Board* b) const = 0;  

    /**
     * @brief Определяет легальность данной позиции на доске 
     * 
     * @param role Игрок, для которого производится оценка 
     * @return true Позиция легальна
     * @return false Позиция нелегальна
     */
    virtual bool isLegal(Role role, Board* b) const = 0;

    /**
     * @brief Конструктор по умолчанию
     * 
     * @param _pos Позиция фигуры
     * @param _color Цвет фигуры
     */
    Figure(Point _pos, FigureColor _color, FigureName _name, int _costControlCell): pos(_pos), color(_color), name(_name), costControlCell(_costControlCell) {};   

    /**
     * @brief Конструктор копирования
     * 
     * @return Figure* Копия фигуры
     */
    virtual Figure* copy() const = 0;

    /**
     * @brief Оценка ценности фигуры в текущем положении
     * 
     * @return double Ценность фигуры
     */
    virtual double getCost() const = 0;

    /**
     * @brief Возвращает список контролируемых полей
     * 
     * @param b Доска, на которой производится проверка
     * @return std::vector<Move> Список контролируемых полей
     */
    virtual std::vector<Move> getControlCell(Board* b) const = 0;  
};

#endif