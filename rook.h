#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figureName.h"
#include "figure.h"
#include "board.h"

/**
 * @class Rook
 * @brief Шахматная фигура - ладья
 */
class Rook : public Figure {
public:
	const double cost = 500.;

	int countStep;

	const double costPos[8][8] 
	{
		{0,  0,  0,  0,  0,  0,  0,  0},
		{5, 10, 10, 10, 10, 10, 10,  5},
		{-5,  0,  0,  0,  0,  0,  0, -5},
		{-5,  0,  0,  0,  0,  0,  0, -5},
		{-5,  0,  0,  0,  0,  0,  0, -5},
		{-5,  0,  0,  0,  0,  0,  0, -5},
		{-5,  0,  0,  0,  0,  0,  0, -5},
		{0,  0,  0,  5,  5,  0,  0,  }
	};

	Rook(Point pos, FigureColor color);
	
	/**
	 * @brief Поиск возможных ходов в заданном направлении
	 *
	 * @param dx Смещение по x
	 * @param dy Смещение по y
	 * @param moves Список ходов, куда нужно записать новые ходы
	 * @param b Доска, на которой происходит поиск ходов
	 * @param ownAttack Возможность атаки своих
	 */
	void findChess(short dx, short dy, std::vector<Move>& moves, Board* b, bool ownAttack) const;

	std::vector<Move> getMoves(Board *b) const;
	Figure* copy() const;
	double getCost() const;
	bool isLegal(Role role, Board* b) const;
	std::vector<Move> getControlCell(Board* b) const;
};

#endif