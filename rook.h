#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

class Rook : public Figure {
public:
	Rook(Point pos, FigureColor color);
	const virtual std::vector<Move> getMoves(const Board *b);
	virtual Rook* copy();
};

#endif