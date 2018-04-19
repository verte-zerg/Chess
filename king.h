#ifndef KING_H
#define KING_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figureName.h"
#include "figure.h"
#include "board.h"

/**
* @class King
* @brief Шахматная фигура - король
*/
class King : public Figure {
public:
	const double cost = 9000.;

	const double costPos[8][8] 
	{
		{-30,-40,-40,-50,-50,-40,-40,-30},
		{-30,-40,-40,-50,-50,-40,-40,-30},
		{-30,-40,-40,-50,-50,-40,-40,-30},
		{-30,-40,-40,-50,-50,-40,-40,-30},
		{-20,-30,-30,-40,-40,-30,-30,-20},
		{-10,-20,-20,-20,-20,-20,-20,-10},
		{ 20, 20,  0,  0,  0,  0, 20, 20},
		{ 20, 30, 10,  0,  0, 10, 30, 2}
	};

	King(Point pos, FigureColor color);
	
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
	double getCost() const;
	bool isLegal(Role role) const;
};

#endif