#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

/**
 * @class Pawn
 * @brief Шахматная фигура - пешка
 */
class Pawn : public Figure {
public:
	Pawn(Point pos, FigureColor color);
	std::vector<Move> getMoves(Board *b) const;
	Figure* copy() const;
};

#endif