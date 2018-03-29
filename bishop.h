#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

/**
 * @class Bishop
 * @brief Шахматная фигура - слон
 */
class Bishop : public Figure {
public:
	Bishop(Point pos, FigureColor color);
	std::vector<Move> getMoves(Board *b) const;
	Bishop* copy() const;
};

#endif