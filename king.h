#ifndef KING_H
#define KING_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

/**
 * @class King
 * @brief Шахматная фигура - король
 */
class King : public Figure {
public:
	King(Point pos, FigureColor color);
	std::vector<Move> getMoves(Board *b) const;
	King* copy() const;
};

#endif