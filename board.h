#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <list>
#include "figure.h"
#include "move.h"
#include "point.h"
#include "role.h"

class Figure;
typedef Figure* figurePtr;

/**
 * @class Board
 * @brief Класс доска, хранящая указатели на фигуры, и основные методы над ними
 */
class Board {
    figurePtr board[8][8]; ///< Массив указателей на фигуры на доске
    std::list<Figure*> cemetery; ///< Кладбище фигур
public: 
    /**
     * @brief Конструктор класса доска по умолчанию
     * 
     */
    Board();

    /**
     * @brief Конструктор копирования класса доска
     * Особенность: кладбище пустое
     * @param b Доска, которую нужно клонировать    
     */
    Board(Board& b);
    
    std::vector<Move> movesHistory; ///< История ходов
    std::vector<Figure*> whiteFigures; ///< Указатели на фигуры игрока Белый
    std::vector<Figure*> blackFigures; ///< Указатель на фигуры игрока Черный
    
    /**
     * @brief Перемещения фигуры
     * 
     * @param move Ход, который нужно сделать
     */
    void moveFigure(Move move);
    

    /**
     * @brief Добавление фигуры
     * 
     * @param figure Фигура, которую нужно добавить     
     */
    void addFigure(Figure* figure);

    /**
     * @brief Удаление фигуры
     * 
     * @param pos Позиция, с которой нужно удалить фигуру     
     */
    void delFigure(Point pos);

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
     * @brief Получение списка вражеских фигур
     * @param _role Цвет игрока, по отношению к которому фигуры являются вражескими
     */
    std::vector<Figure*>& getEnemyFigures(Role _role);

    /**
     * @brief Получение списка собственных фигур
     * @param _role Цвет игрока, фигуры которого нужно получить
     */
    std::vector<Figure*>& getOwnFigures(Role _role);

    /**
     * @brief Функция отмены последего хода
     * 
     */
    void undoMove();
};

#endif