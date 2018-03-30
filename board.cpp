#include "board.h"
#include <cstddef>
#include "figureColor.h"
#include "allFigures.h"

void Board::moveFigure(Move move) {
    //Добавить обработку взятия на проходе и рокировку
    if ((*this)[move.to] != NULL)
    {
        cemetery.push_back((*this)[move.to]);

        for (int i = 0; i < whiteFigures.size(); i++)
            if (move.to == whiteFigures[i]->pos)
                whiteFigures.erase(whiteFigures.begin() + i);

        for (int i = 0; i < blackFigures.size(); i++)
            if (move.to == blackFigures[i]->pos)
                blackFigures.erase(blackFigures.begin() + i);
    }

    movesHistory.push_back(move);

    (*this)[move.to] = (*this)[move.from];
    (*this)[move.from] = NULL;
}

Board::Board() {}


Board::Board(Board& b) 
{    
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (b.board[i][j] != NULL) 
            {                
                Figure* f = b.board[i][j]->copy();
                board[i][j] = f;
                if (f->color == FigureColor::white)
                    whiteFigures.push_back(f);
                if (f->color == FigureColor::black)
                    blackFigures.push_back(f);                    
            }
    
    std::list<Figure*> copyCemetery(b.cemetery);

    while (!copyCemetery.empty())
    {
        cemetery.push_front(copyCemetery.back());
        copyCemetery.pop_back();
    }
    
    movesHistory = std::vector<Move>(b.movesHistory);
}

void Board::addFirure(Figure* figure)
{
    (*this)[figure->pos] = figure;
    if (figure->color == FigureColor::white)
        whiteFigures.push_back(figure);
    if (figure->color == FigureColor::black)
        blackFigures.push_back(figure);
}

void Board::arrangement() 
{
    /*
    //Добавляем пешки
    for (int i = 0; i < 8; i++)
    {
        addFirure(new Pawn(Point(i, 1),  FigureColor::white));
        addFirure(new Pawn(Point(i, 6),  FigureColor::black));       
    }    
    */
   
    //Добавляем ладей
    addFirure(new Rook(Point(0, 0),  FigureColor::white));
    addFirure(new Rook(Point(7, 0),  FigureColor::white));
    addFirure(new Rook(Point(0, 7),  FigureColor::black));
    addFirure(new Rook(Point(7, 7),  FigureColor::black));

    //Добавляем коней
    addFirure(new Knight(Point(1, 0),  FigureColor::white));
    addFirure(new Knight(Point(6, 0),  FigureColor::white));
    addFirure(new Knight(Point(1, 7),  FigureColor::black));
    addFirure(new Knight(Point(6, 7),  FigureColor::black));

    //Добавление слонов
    addFirure(new Bishop(Point(2, 0),  FigureColor::white));
    addFirure(new Bishop(Point(5, 0),  FigureColor::white));
    addFirure(new Bishop(Point(2, 7),  FigureColor::black));
    addFirure(new Bishop(Point(5, 7),  FigureColor::black));

    //Добавление королев
    addFirure(new Queen(Point(3, 0),  FigureColor::white));
    addFirure(new Queen(Point(3, 7),  FigureColor::black));

    //Добавление королей
    addFirure(new King(Point(4, 0),  FigureColor::white));
    addFirure(new King(Point(4, 7),  FigureColor::black));
}


figurePtr& Board::operator[](Point pos)
{
    return board[pos.x][pos.y];
}


void Board::undoMove() {
    Move lastMove = movesHistory[movesHistory.size() - 1];

    (*this)[lastMove.from] = (*this)[lastMove.to];

    if (lastMove.isAttack)
    {        
        Figure* deadFigure = cemetery.back();

        (*this)[lastMove.to] = deadFigure;

        if (deadFigure->color == FigureColor::white)
            whiteFigures.push_back(deadFigure);            
        if (deadFigure->color == FigureColor::black)
            blackFigures.push_back(deadFigure);

        cemetery.pop_back();
    }
}