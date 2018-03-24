#include "board.h"
#include <cstddef>
#include "figureColor.h"

void Board::moveFigure(Move move) {
    if ((*this)[move.to] != NULL)
    {
        cemetery.push((*this)[move.to]);

        for (int i = 0; i < whiteFigures.size(); i++)
            if (move.from == whiteFigures[i]->pos)
                whiteFigures.erase(whiteFigures.begin() + i);

        for (int i = 0; i < blackFigures.size(); i++)
            if (move.from == blackFigures[i]->pos)
                blackFigures.erase(blackFigures.begin() + i);
    }

    movesHistory.push_back(move);

    (*this)[move.to] = (*this)[move.from];
    (*this)[move.to] = NULL;
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
    
    movesHistory = std::vector<Move>(b.movesHistory);
}


void Board::arrangement() {
    
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
        Figure* deadFigure = cemetery.top();
        (*this)[lastMove.to] = deadFigure;

        if (deadFigure->color == FigureColor::white)
            whiteFigures.push_back(deadFigure);            
        if (deadFigure->color == FigureColor::black)
            blackFigures.push_back(deadFigure);

        cemetery.pop();      
    }
}