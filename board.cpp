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
        delFigure(move.to);
    }

    //Трансформация фигуры;
    if ((*this)[move.from]->name == FigureName::pawn && move.figureName != FigureName::pawn)
    {      
        Figure* oldFigure = (*this)[move.from];
        delFigure(move.from);
        switch (move.figureName)
        {
            case FigureName::queen : addFigure(new Queen(move.from, oldFigure->color));
                break;
            case FigureName::rook : addFigure(new Rook(move.from, oldFigure->color));
                break;
            case FigureName::bishop : addFigure(new Bishop(move.from, oldFigure->color));
                break;
            case FigureName::knight : addFigure(new Knight(move.from, oldFigure->color));
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
            else
                board[i][j] = NULL;
    
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

void Board::addFigure(Figure* figure)
{
    (*this)[figure->pos] = figure;
    if (figure->color == FigureColor::white)
        whiteFigures.push_back(figure);
    if (figure->color == FigureColor::black)
        blackFigures.push_back(figure);
}

void Board::delFigure(Point pos)
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
        addFigure(new Pawn(Point(i, 1),  FigureColor::white));
        addFigure(new Pawn(Point(i, 6),  FigureColor::black));       
    } 
   
    //Добавляем ладей
    addFigure(new Rook(Point(0, 0),  FigureColor::white));
    addFigure(new Rook(Point(7, 0),  FigureColor::white));
    addFigure(new Rook(Point(0, 7),  FigureColor::black));
    addFigure(new Rook(Point(7, 7),  FigureColor::black));

    //Добавляем коней
    addFigure(new Knight(Point(1, 0),  FigureColor::white));
    addFigure(new Knight(Point(6, 0),  FigureColor::white));
    addFigure(new Knight(Point(1, 7),  FigureColor::black));
    addFigure(new Knight(Point(6, 7),  FigureColor::black));

    //Добавление слонов
    addFigure(new Bishop(Point(2, 0),  FigureColor::white));
    addFigure(new Bishop(Point(5, 0),  FigureColor::white));
    addFigure(new Bishop(Point(2, 7),  FigureColor::black));
    addFigure(new Bishop(Point(5, 7),  FigureColor::black));

    //Добавление королев
    addFigure(new Queen(Point(3, 0),  FigureColor::white));
    addFigure(new Queen(Point(3, 7),  FigureColor::black));

    //Добавление королей
    addFigure(new King(Point(4, 0),  FigureColor::white));
    addFigure(new King(Point(4, 7),  FigureColor::black));
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
        delFigure(lastMove.to);
        addFigure(new Pawn(lastMove.to, oldFigure->color));
    }

    (*this)[lastMove.to]->pos = lastMove.from; 
    (*this)[lastMove.from] = (*this)[lastMove.to];
    (*this)[lastMove.to] = NULL;

    if (lastMove.isAttack)
    {        
        addFigure(cemetery.back());
        cemetery.pop_back();        
    }
}

bool Board::isLegal(Role role) const
{
    int numberOfPawns = 8;
    int tmp;

    #pragma region Проверка количества королей
    if (getNumberOfFigures(FigureName::king, FigureColor::black) != 1)
        return false;

    if (getNumberOfFigures(FigureName::king, FigureColor::white) != 1)
        return false;
    #pragma endregion
    
    #pragma region Проверка количества белых фигур
    tmp = getNumberOfFigures(FigureName::knight, FigureColor::white);
    if (tmp > 10)
        return false;
    if (tmp > 2)
        numberOfPawns -= (tmp - 2);

    tmp = getNumberOfFigures(FigureName::bishop, FigureColor::white);
    if (tmp > 10)
        return false;
    if (tmp > 2)
        numberOfPawns -= (tmp - 2);

    tmp = getNumberOfFigures(FigureName::rook, FigureColor::white);
    if (tmp > 10)
        return false;    
    if (tmp > 2)
        numberOfPawns -= (tmp - 2);

    tmp = getNumberOfFigures(FigureName::queen, FigureColor::white);
    if (tmp > 9)
        return false;    
    if (tmp > 1)
        numberOfPawns -= (tmp - 1);

    tmp = getNumberOfFigures(FigureName::pawn, FigureColor::white);
    if (tmp > 8 || numberOfPawns < 0)
        return false;    
    #pragma endregion    

    numberOfPawns = 0;
    #pragma region Проверка количества черных фигур
    tmp = getNumberOfFigures(FigureName::knight, FigureColor::black);
    if (tmp > 10)
        return false;
    if (tmp > 2)
        numberOfPawns -= (tmp - 2);

    tmp = getNumberOfFigures(FigureName::bishop, FigureColor::black);
    if (tmp > 10)
        return false;
    if (tmp > 2)
        numberOfPawns -= (tmp - 2);

    tmp = getNumberOfFigures(FigureName::rook, FigureColor::black);
    if (tmp > 10)
        return false;    
    if (tmp > 2)
        numberOfPawns -= (tmp - 2);

    tmp = getNumberOfFigures(FigureName::queen, FigureColor::black);
    if (tmp > 9)
        return false;    
    if (tmp > 1)
        numberOfPawns -= (tmp - 1);

    tmp = getNumberOfFigures(FigureName::pawn, FigureColor::black);
    if (tmp > 8 || numberOfPawns < 0)
        return false;    
    #pragma endregion       
}

ushort Board::getNumberOfFigures(const FigureName name, const FigureColor color) const
{
    ushort count = 0;

    for (uint i = 0; i < 8; i++)
        for (uint j = 0; j < 8; j++)
            if (board[i][j] != NULL)
                if (board[i][j]->name == name && board[i][j]->color == color)
                    count++;

    return count;
}