#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

class Pawn : public Figure {
public:
	Pawn(Point pos, FigureColor color);
	const virtual std::vector<Move> getMoves(const Board *b);
	virtual Pawn* copy();
};

#endif