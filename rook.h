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
	/**
	 * @brief Поиск возможных ходов в заданном направлении
	 *
	 * @param dx Смещение по x
	 * @param dy Смещение по y
	 * @param moves Список ходов, куда нужно записать новые ходы
	 * @param b Доска, на которой происходит поиск ходов
	 */
	void findChess(short dx, short dy, std::vector<Move>& moves, Board* b) const;

	std::vector<Move> getMoves(Board *b) const;
	Figure* copy() const;
};

#endif