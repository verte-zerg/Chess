#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

class Queen : public Figure {
public:
	Queen(Point pos, FigureColor color);
	const virtual std::vector<Move> getMoves(const Board *b);
	const virtual Queen* copy();
};

#endif