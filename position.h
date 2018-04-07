#ifndef POSITION_H
#define POSITION_H

#include <vector>

#include "role.h"
#include "move.h"
#include "board.h"


class Position
{

public:
	Position* prev; ///< Указатель на предыдущую ситуацию

	std::vector<Position*> next; ///< Возможные следующие ситуации из данной ситуации
	std::vector<Move> possibleMoves; ///< Все возможные ходы из данной ситуации

	Role whoseRole; ///< Цвет игрока, ход которого рассчитывается в этой ситуации
	Move lastMove; ///< Ход, который привел к данной ситуации
	Move bestNextMove; // Лучший ход из данной позиции для текущей стороны

	uint depth; //Глубина текущего хода в полуходах

	double assessment; ///< Оценка данной ситуации
	double bestAssessment; ///< Лучшая оценка для текущей ситуации

    /**
     * @brief Конструктор класса Position
     * 
     * @param _depth Глубина текущего хода в полуходах
     * @param _role Цвет игрока, ход которого рассчитывается в этой ситуации
     */
	Position(uint _depth, Role _role);

    /**
     * @brief Метод, получающий все возможные ходы
     * 
     * @param b Доска, для которой находятся ходы
     */
	void canvass(Board* b); //метод, который спрашивает у фигур возможные ходы 
};

#endif