#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figure.h"
#include "board.h"

/**
 * @class Knight
 * @brief Шахматная фигура - конь
 */
class Knight : public Figure {
public:
	Knight(Point pos, FigureColor color);
	std::vector<Move> getMoves(Board *b) const;
	Knight* copy() const;
};

#endif