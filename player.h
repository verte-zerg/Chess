#ifndef PLAYER_H
#define PLAYER_H

#include "role.h"
#include "board.h"
#include "position.h"
#include "message.h"

/**
 * @class Player
 * @brief Класс игрока, который осуществляет выбор лучшего хода
 */
class Player
{
	const uint calcDepth; ///< Глубина просчета в полуходах
	const Role role; ///< Цвет игрока
	Board* ownBoard; ///< Собственная доска
	
    /**
     * @brief 
     * 
     * @param pos 
     * @return double 
     */
	double costFunc(const Position* pos);

    /**
     * @brief Функция, просчитывающая лучший ход 
     * 
     * @return Message* Возвращает лучший ход
     */
	Message* thinking();

    /**
     * @brief Рекурсивная функция, строящее дерево выбора лучшего хода
     * 
     * @param initPos Начальная позиция 
     */
	Move getBestMove();

    /**
     * @brief Функция отправки сообщения
     * 
     * @param m Сообщение, которое нужно отправить
     */
    void sendMessage(Message* m);

public:
    /**
     * @brief Конструктор класса игрок
     * 
     * @param _role Цвет игрока
     * @param _calcDepth Глубина просчета в полуходах
     */
	Player(Role _role, uint _calcDepth);

    /**
     * @brief Функция ожидания приёма сообщения
     */
    void recieveMessage();    
};

#endif