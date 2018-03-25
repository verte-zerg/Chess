#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

class Bishop : public Figure {
public:
	Bishop(Point pos, FigureColor color);
	const virtual std::vector<Move> getMoves(const Board *b);
	virtual Bishop* copy();
};

#endif