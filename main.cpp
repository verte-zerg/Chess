#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>

#include "board.h"
#include "player.h"
#include "manager.h"
#include "point.h"
#include "figureColor.h"
#include "allFigures.h"
#include "role.h"
#include "stateGame.h"

Board* globalBoard;

Message* msg = NULL;
std::condition_variable checkMessage;
std::mutex lockAccess;
StateGame stateGame = StateGame::game;

void addFig(std::string name, int x, int y, Board* b, FigureColor color)
{
    if ((*b)[Point(x, y)] != NULL)
    {
        std::cout << "В данной позиции находится другая фигура.\n";
        return;
    }

    if (x > 7 || x < 0 || y > 7 || y < 0)
    {
        std::cout << "Данная позиции находится за пределами доски.\n";
        return;
    }

    if (name == "K")
        b->addFigure(new Knight(Point(x, y), color));
    else if (name == "B")
        b->addFigure(new Bishop(Point(x, y), color));
    else if (name == "R")
        b->addFigure(new Rook(Point(x, y), color));
    else if (name == "Q")
        b->addFigure(new Queen(Point(x, y), color));
    else if (name == "Kg")
        b->addFigure(new King(Point(x, y), color));
    else if (name == "P")
        b->addFigure(new Pawn(Point(x, y), color));
    else
    {
        std::cout << "Неизвестное название фигуры.\n";
        return;
    }
}

void consoleArrangement(Board* b)
{
    //std::cout << "Стандартная расстановка (y(Yes), n(No))? ";

    char ch;
    std::ifstream input("input");
    input >> ch;

    if (ch == 'y')
        b->arrangement();
    else if (ch = 'n')
    {
        std::string in, name;
        int x, y;
        char parse[1];
        FigureColor color = FigureColor::white;     
        //std::cout << "Ввод фигур в формате [Name][X][Y].\nСначала вводятся белые, после ввода '0' черные. Следующий ноль - завершение ввода.\n";   
        while (true)
        {                                    
            input >> in;            
            if (in == "0")
            {
                if (color == FigureColor::white)
                {
                    color = FigureColor::black;
                    //std::cout << "Ввод черных фигур:\n";
                    continue;
                }
                else
                    break;
            }  

            for (uint i = 0; i < in.size(); i++)
                if (in[i] == ' ')
                {
                    in.erase(i, 1);
                    i--;
                }

            in.copy(parse, 1, in.size() - 2);
            x = int(parse[0]) - 97;            
            in.copy(parse, 1, in.size() - 1);
            y = atoi(parse) - 1;
            name = in.substr(0, in.size() - 2);
            addFig(name, x, y, b, color);                        
        }
    }
}

//Ненужный метод
void loopGetMoves(Board* b)
{
    std::string in;
    int x, y;
    char parse[1];
    std::vector<Move> moves;
    while (true)
    {
        std::cout << "Введите координаты фигуры: ";
        std::cin >> in;
        in.copy(parse, 1, 0);
        x = int(parse[0]) - 97;            
        in.copy(parse, 1, 1);
        y = atoi(parse) - 1;
        if ((*b)[Point(x, y)] == NULL)
        {
            std::cout << "В данной позиции фигур нет.\n";
            continue;
        }
        moves = (*b)[Point(x, y)]->getMoves(b);
        for (int i = 0; i < moves.size(); i++)
            std::cout << moves[i] << std::endl;
    }
}

int main()
{
    globalBoard = new Board();            
    consoleArrangement(globalBoard);    
    plotInConsole();    

    if (!globalBoard->isLegal(Role::playerWhite))
    {
        std::cout << "Некорректная расстановка." << std::endl;
        return 0;
    }

    Player playerWhite(Role::playerWhite, 5), playerBlack(Role::playerBlack, 3);
    Manager manager;

    std::thread mng(&Manager::recieveMessage, std::ref(manager));
    std::thread plW(&Player::recieveMessage, std::ref(playerWhite));
    std::thread plB(&Player::recieveMessage, std::ref(playerBlack));

    mng.join();

    return 0;
}