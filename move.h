#ifndef MOVE_H
#define MOVE_H

#include "point.h"
#include "figureName.h"
#include "typeMove.h"
#include <iostream>
#include <cstring>

/**
 * @class Move
 * @brief Структура, содержащая информацию о ходе
 */
struct Move 
{
public: 
    Point from; ///< Начальное положение фигуры
    Point to; ///< Конечное положение фигуры
    TypeMove type; ///< Тип хода
    FigureName figureName; ///< Тип фигуры

    Move()
    {
        from = Point(0, 0);
        to = Point(0, 0);
        type = TypeMove::empty;
    }

    Move(Point _from, Point _to, TypeMove _type, FigureName _figureName)
    {
        from = _from;
        to = _to;
        type = _type;
        figureName = _figureName;
    }

    Move(const Move& m)
    {
        from = m.from;
        to = m.to;
        type = m.type;
        figureName = m.figureName;
    }

    friend std::ostream& operator << (std::ostream &os, const Move &m)
    {
        std::string name, type;        
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
        }

        switch (m.type)
        {
            case TypeMove::attack : type = "атака";
                break;
            case TypeMove::attack_and_transform : type = "атака и трансформация";
                break;
            case TypeMove::castling : type = "рокировка";
                break;
            case TypeMove::empty : type = "пустой ход";
                break;
            case TypeMove::en_passant : type = "взятие на проходе";
                break;
            case TypeMove::move : type = "ход";
                break;
            case TypeMove::transform : type = "трансформация";
                break;
        }

        os << type << " -> " << name << char(97 + m.from.x) << m.from.y + 1 << " " << char(97 + m.to.x) << m.to.y + 1 << " ";
        return os;
    }
};

#endif