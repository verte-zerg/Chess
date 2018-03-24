#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "figure.h"
#include "move.h"
#include "point.h"
#include <stack>

class Figure;
typedef Figure* figurePtr;

/**
 * @brief Класс доска, хранящая указатели на фигуры, и основные методы над ними
 * 
 */
class Board {
public: 
    /**
     * @brief Конструктор класса доска по умолчанию
     * 
     */
    Board();

    /**
     * @brief Конструктор копированиякласса доска
     * Особенность: кладбище пустое
     * @param b Доска, которую нужно клонировать
     *      */
    Board(Board& b);

    figurePtr board[8][8]; ///< Массив указателей на фигуры на доске
    std::vector<Move> movesHistory; ///< История ходов
    std::vector<Figure*> whiteFigures; ///< Указатели на фигуры игрока Белый
    std::vector<Figure*> blackFigures; ///< Указатель на фигуры игрока Черный
    std::stack<Figure*> cemetery; ///< Кладбище фигур
    
    /**
     * @brief Функция перемещения фигуры
     * 
     * @param move Ход, который нужно сделать
     */
    void moveFigure(Move move);
    

    /**
     * @brief Расстановка фигур в начальные состояние
     * 
     */
    void arrangement();    

    /**
     * @brief Возвращает ссылку на указатель фигуры в указанной позиции
     * 
     * @param pos Проверяемая позиция
     * @return figurePtr& Ссылка на указатель фигуры
     */
    figurePtr& operator[](Point pos);
    
    /**
     * @brief Функция отмены последего хода
     * 
     */
    void undoMove();
};

#endif