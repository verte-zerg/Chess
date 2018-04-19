#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "point.h"
#include "move.h"
#include "figureColor.h"
#include "figureName.h"
#include "figure.h"
#include "board.h"

/**
 * @class Pawn
 * @brief Шахматная фигура - пешка
 */
class Pawn : public Figure {
public:
	const double cost = 100.;

	const double costPos[8][8] 
	{
		{0,  0,  0,  0,  0,  0,  0,  0},
		{50, 50, 50, 50, 50, 50, 50, 50},
		{10, 10, 20, 30, 30, 20, 10, 10},
		{5,  5, 10, 25, 25, 10,  5,  5},
		{0,  0,  0, 20, 20,  0,  0,  0},
		{5, -5,-10,  0,  0,-10, -5,  5},
		{5, 10, 10,-20,-20, 10, 10,  5},
		{0,  0,  0,  0,  0,  0,  0,  0}
	};

	Pawn(Point pos, FigureColor color);

	/**
	 * @brief Поиск возможных ходов в заданном направлении
	 *
	 * @param dx Смещение по x	 
	 * @param canAttack Проверка атакующего хода
	 * @param moves Список ходов, куда нужно записать новые ходы
	 * @param b Доска, на которой происходит поиск ходов
	 */
	void findChess(short dx, bool canAttack, std::vector<Move>& moves, Board* b) const;

	std::vector<Move> getMoves(Board *b) const;
	Figure* copy() const;
	double getCost() const;
	bool isLegal(Role role) const;
};

#endif