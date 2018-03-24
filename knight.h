#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

class Knight : public Figure {
public:
	Knight(Point pos, FigureColor color);
	const virtual std::vector<Move> getMoves(const Board *b);
	const virtual Knight* copy();
};

#endif