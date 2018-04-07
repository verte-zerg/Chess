#ifndef MOVE_H
#define MOVE_H

#include "point.h"
#include "figureName.h"
#include <iostream>
#include <cstring>

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

    Move()
    {
        from = Point(0, 0);
        to = Point(0, 0);
        isAttack = false;
    }

    Move(Point _from, Point _to, bool _isAttack, FigureName _figureName)
    {
        from = _from;
        to = _to;
        isAttack = _isAttack;
        figureName = _figureName;
    }

    Move(const Move& m)
    {
        from = m.from;
        to = m.to;
        isAttack = m.isAttack;
        figureName = m.figureName;
    }

    friend std::ostream& operator << (std::ostream &os, const Move &m)
    {
        std::string name;        
        switch (m.figureName)
        {
            case FigureName::pawn : name = "";
                break;
            case FigureName::knight : name = "K";
                break;
            case FigureName::bishop : name = "B";
                break;
            case FigureName::rook : name = "R";
                break;
            case FigureName::queen : name = "Q";
                break;
            case FigureName::king : name = "Kg";
                break;
        default:
            break;
        }
        os << name << char(97 + m.from.x) << m.from.y + 1 << " " << char(97 + m.to.x) << m.to.y + 1;
        return os;
    }
};

#endif