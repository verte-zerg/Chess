#ifndef KING_H
#define KING_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

class King : public Figure {
public:
	King(Point pos, FigureColor color);
	const virtual std::vector<Move> getMoves(const Board *b);
	const virtual King* copy();
};

#endif