#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figureName.h"
#include "figure.h"
#include "board.h"

/**
 * @class Queen
 * @brief Шахматная фигура - ферзь
 */
class Queen : public Figure {
public:
	const double cost = 900.;

	const double costPos[8][8] 
	{
		{-20,-10,-10, -5, -5,-10,-10,-20},
		{-10,  0,  0,  0,  0,  0,  0,-10},
		{-10,  0,  5,  5,  5,  5,  0,-10},
		{ -5,  0,  5,  5,  5,  5,  0, -5},
		{  0,  0,  5,  5,  5,  5,  0, -5},
		{-10,  5,  5,  5,  5,  5,  0,-10},
		{-10,  0,  5,  0,  0,  0,  0,-10},
		{-20,-10,-10, -5, -5,-10,-10,-2}
	};

	Queen(Point pos, FigureColor color);

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