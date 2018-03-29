#ifndef MOVE_H
#define MOVE_H

#include "point.h"
#include "figureName.h"

/**
 * @brief Класс, 
 * 
 */
struct Move {
public: 
    Point from; ///< Начальное положение фигуры
    Point to; ///< Конечное положение фигуры
    bool isAttack; ///< Является ли ход атакующим
    FigureName figureName; ///< Тип фигуры

    Move(Point _from, Point _to, bool _isAttack, FigureName _figureName)
    {
        from = _from;
        to = _to;
        isAttack = _isAttack;
        figureName = _figureName;
    }
};

#endif