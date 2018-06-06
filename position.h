#ifndef POSITION_H
#define POSITION_H

#include <vector>

#include "role.h"
#include "move.h"
#include "board.h"

/**
 * @class Position
 * @brief Класс-дерево, производящий рекурсивную оценку качества хода
 */
class Position
{
public:	
    const int stalemate = 90000; ///< Константа для значения пата
    const int checkmate = 100000; ///< Константа для значения мата

	std::vector<Move> possibleMoves; ///< Все возможные ходы из данной ситуации

    Role whoCall; ///< Цвет игрока, который вызвал оценку позиций
	Role whoseRole; ///< Цвет игрока, ход которого рассчитывается в этой ситуации
	Move lastMove; ///< Ход, который привел к данной ситуации

	uint maxDepth; ///< Максимальная глубина в полуходах    
    uint moveDepth; ///< Номер итерации на которой был расчитан лучший полуход

	double assessment; ///< Оценка данной ситуации
	double bestAssessment; ///< Лучшая оценка для текущей ситуации

    /**
     * @brief Конструктор класса Position
     * 
     * @param _depth Глубина текущего хода в полуходах
     * @param _role Цвет игрока, ход которого рассчитывается в этой ситуации
     */
	Position(uint _maxDepth, Role _role, Role _whoCall);

    /**
     * @brief Функция оценки доски
     * 
     * @param b Доска, которую нужно оценить
     * @return double Ценность позиции
     */
	double costFunc(Board* b);

    /**
     * @brief Get the Best Assessment object
     *      
     * @param b 
     * @param nowDepth 
     * @return int 
     */
    int getBestAssessment(Board* b, uint nowDepth);

    /**
     * @brief Метод, получающий все возможные ходы
     * @param b Доска, для которой находятся ходы
     */
	void canvass(Board* b, Role role); //метод, который спрашивает у фигур возможные ходы 
};

#endif