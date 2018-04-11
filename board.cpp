#include "board.h"
#include <cstddef>
#include "figureColor.h"
#include "allFigures.h"
#include <typeinfo>

void Board::moveFigure(Move move) {
    movesHistory.push_back(move);
    
    if (move.to == move.from)
        return;
    //Добавить обработку взятия на проходе и рокировку
    if ((*this)[move.to] != NULL)
    {
        cemetery.push_back((*this)[move.to]);
        delFirure(move.to);
    }

    //Трансформация фигуры;
    if ((*this)[move.from]->name == FigureName::pawn && move.figureName != FigureName::pawn)
    {      
        Figure* oldFigure = (*this)[move.from];
        delFirure(move.from);
        switch (move.figureName)
        {
            case FigureName::queen : addFirure(new Queen(move.from, oldFigure->color));
                break;
            case FigureName::rook : addFirure(new Rook(move.from, oldFigure->color));
                break;
            case FigureName::bishop : addFirure(new Bishop(move.from, oldFigure->color));
                break;
            case FigureName::knight : addFirure(new Knight(move.from, oldFigure->color));
                break;
        }
        
        move.figureName = FigureName::pawn;
    }

    (*this)[move.from]->pos = move.to;
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

std::vector<Figure*>& Board::getEnemyFigures(Role _role)
{
    if (_role == Role::playerWhite)
        return blackFigures;
    else if (_role == Role::playerBlack)
        return whiteFigures;
}

std::vector<Figure*>& Board::getOwnFigures(Role _role)
{
    if (_role == Role::playerWhite)
        return whiteFigures;
    else if (_role == Role::playerBlack)
        return blackFigures;
}

void Board::addFirure(Figure* figure)
{
    (*this)[figure->pos] = figure;
    if (figure->color == FigureColor::white)
        whiteFigures.push_back(figure);
    if (figure->color == FigureColor::black)
        blackFigures.push_back(figure);
}

void Board::delFirure(Point pos)
{
    for (int i = 0; i < whiteFigures.size(); i++)
        if (pos == whiteFigures[i]->pos)
            whiteFigures.erase(whiteFigures.begin() + i);

    for (int i = 0; i < blackFigures.size(); i++)
        if (pos == blackFigures[i]->pos)
            blackFigures.erase(blackFigures.begin() + i);

    (*this)[pos] = NULL;
}

void Board::arrangement() 
{    
    //Добавляем пешки
    for (int i = 0; i < 8; i++)
    {
        addFirure(new Pawn(Point(i, 1),  FigureColor::white));
        addFirure(new Pawn(Point(i, 6),  FigureColor::black));       
    } 
   
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


void Board::undoMove() 
{
    //Добавить обработку отмены рокировки, взятия на проходе, трансформации
    Move lastMove = movesHistory[movesHistory.size() - 1];
    movesHistory.pop_back();

    if (lastMove.to == lastMove.from)
        return;

    if ((*this)[lastMove.to]->name != FigureName::pawn && lastMove.figureName == FigureName::pawn)
    {
        Figure* oldFigure = (*this)[lastMove.to];
        delFirure(lastMove.to);
        addFirure(new Pawn(lastMove.to, oldFigure->color));
    }

    (*this)[lastMove.to]->pos = lastMove.from; 
    (*this)[lastMove.from] = (*this)[lastMove.to];
    (*this)[lastMove.to] = NULL;

    if (lastMove.isAttack)
    {        
        addFirure(cemetery.back());
        cemetery.pop_back();        
    }
}