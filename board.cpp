#include "board.h"
#include <cstddef>
#include "figureColor.h"
#include "allFigures.h"
#include "typeMove.h"
#include <typeinfo>

void Board::moveFigure(Move move)
{
    movesHistory.push_back(move);
    
    //Обработка хода empty
    if (move.type == TypeMove::empty)    
        return;

    //Уничтожение фигуры
    if (move.type == TypeMove::attack || move.type == TypeMove::attack_and_transform)
    {
        cemetery.push_back((*this)[move.to]);
        delFigure(move.to);
    }

    //Трансформация фигуры
    if (move.type == TypeMove::transform)
    {      
        Figure* oldFigure = (*this)[move.from];
        delFigure(move.from);
        switch (move.figureName)
        {
            case FigureName::queen : addFigure(new Queen(move.to, oldFigure->color));
                break;
            case FigureName::rook : addFigure(new Rook(move.to, oldFigure->color));
                break;
            case FigureName::bishop : addFigure(new Bishop(move.to, oldFigure->color));
                break;
            case FigureName::knight : addFigure(new Knight(move.to, oldFigure->color));
                break;
        }
        
        move.figureName = FigureName::pawn;
        movesHistory.pop_back();
        movesHistory.push_back(move);
        return;
    }

    //Счетчик количества ходов для проверки возможности рокировки        
    if (move.figureName == FigureName::rook)
        ((Rook*)(*this)[move.from])->countStep++;

    if (move.figureName == FigureName::king)
        ((King*)(*this)[move.from])->countStep++;    

    //Рокировка
    if (move.type == TypeMove::castling)
    {
        int dxKing, dxRook;

        Point fromRook = move.to;
        Point toRook = fromRook;

        Point fromKing = move.from;
        Point toKing = fromKing;

        if (move.to.x > move.from.x)
        {
            dxKing = 2;
            dxRook = -2;
        }
        else
        {
            dxKing = -2;
            dxRook = 3;
        }     

        toRook.x += dxRook;  
        toKing.x += dxKing; 

        (*this)[fromKing]->pos = toKing;
        (*this)[toKing] = (*this)[fromKing];
        (*this)[fromKing] = NULL;

        (*this)[fromRook]->pos = toRook;
        (*this)[toRook] = (*this)[fromRook];
        (*this)[fromRook] = NULL;
        return;
    }

    //Взятие на проходе
    if (move.type == TypeMove::en_passant)
    {
        cemetery.push_back((*this)[Point(move.to.x, move.from.y)]);
        delFigure(move.to);
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
    Move lastMove = movesHistory.back();
    movesHistory.pop_back();

    if (lastMove.type == TypeMove::empty)
        return;

    //Счетчик количества ходов для проверки возможности рокировки
    if (lastMove.type != castling)
    {
        if (lastMove.figureName == FigureName::rook)
            ((Rook*)(*this)[lastMove.to])->countStep--;

        if (lastMove.figureName == FigureName::king)
            ((King*)(*this)[lastMove.to])->countStep--;
    }

    //Отмена трансформации
    if (lastMove.type == TypeMove::transform || lastMove.type == TypeMove::attack_and_transform)
    {
        Figure* oldFigure = (*this)[lastMove.to];
        delFigure(lastMove.to);
        addFigure(new Pawn(lastMove.to, oldFigure->color));        
    }
    
    //Отмена рокировки
    if (lastMove.type == TypeMove::castling)
    {
        int dxKing, dxRook;

        Point toRook = lastMove.to;
        Point fromRook = toRook;

        Point toKing = lastMove.from;
        Point fromKing = toKing;        

        if (lastMove.to.x > lastMove.from.x)
        {
            dxKing = 2;
            dxRook = -2;
        }
        else
        {
            dxKing = -2;
            dxRook = 3;
        }     

        fromRook.x += dxRook;  
        fromKing.x += dxKing; 

        (*this)[fromKing]->pos = toKing;
        (*this)[toKing] = (*this)[fromKing];
        (*this)[fromKing] = NULL;

        (*this)[fromRook]->pos = toRook;
        (*this)[toRook] = (*this)[fromRook];
        (*this)[fromRook] = NULL;

        return;
    }

    (*this)[lastMove.to]->pos = lastMove.from; 
    (*this)[lastMove.from] = (*this)[lastMove.to];
    (*this)[lastMove.to] = NULL;

    if (lastMove.type == TypeMove::attack || lastMove.type == TypeMove::en_passant || lastMove.type == TypeMove::attack_and_transform)
    {        
        addFigure(cemetery.back());
        cemetery.pop_back();        
    }
}

bool Board::isLegal(Role role)
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

    #pragma region Проверка на двойной шах
    bool whiteKingAttack = false;
    bool blackKingAttack = false;

    std::vector<Move> possibleMoves, tmpMove;
    for (ushort i = 0; i < 8; i++)
        for (ushort j = 0; j < 8; j++)
            if (board[i][j] != NULL && board[i][j]->name != FigureName::king)
            {   
                tmpMove = board[i][j]->getMoves(this);
                possibleMoves.insert(possibleMoves.end(), tmpMove.begin(), tmpMove.end());
            }
    
    for(Move move : possibleMoves)
        if ((move.type == TypeMove::attack || move.type == TypeMove::attack_and_transform) 
            && (*this)[move.to]->name == FigureName::king)
        {
            if ((*this)[move.to]->color == FigureColor::white)
                whiteKingAttack = true;
            else
                blackKingAttack = true;
        }
            
    if (whiteKingAttack && blackKingAttack)
        return false; 
    #pragma endregion

    #pragma region Проверка каждой фигуры на легальность
    for (ushort i = 0; i < 8; i++)
        for (ushort j = 0; j < 8; j++)
            if (board[i][j] != NULL)
                if (!board[i][j]->isLegal(Role::playerWhite, this))
                    return false;
    #pragma endregion

    return true;
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

bool Board::cellIsAttacked(Point cell, Role role)
{
    std::vector<Figure*> enemy = getEnemyFigures(role);

    std::vector<Move> tmpMoves;

    for(Figure* fig : enemy)
    {
        tmpMoves = fig->getControlCell(this);
        for(Move move : tmpMoves)
            if (move.to == cell)
                return true;
    }

    return false;
}