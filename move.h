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
    Point from, to;
    bool isAttack;
    FigureName figureName;
};

#endif