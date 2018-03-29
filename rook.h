#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

/**
 * @class Rook
 * @brief Шахматная фигура - ладья
 */
class Rook : public Figure {
public:
	Rook(Point pos, FigureColor color);
	std::vector<Move> getMoves(Board *b) const;
	Rook* copy() const;
};

#endif