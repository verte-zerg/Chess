#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "board.h"

class Board;

class Figure {
public:     
    Point pos;
    FigureColor color;

    const virtual std::vector<Move> getMoves(const Board* b) = 0;   
    Figure(Point _pos, FigureColor _color); 
    virtual Figure* copy() = 0;
};

#endif