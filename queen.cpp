#include "queen.h"

Queen::Queen(Point _pos, FigureColor _figureColor): Figure(_pos, _figureColor, FigureName::queen, 5.) {};

void Queen::findChess(short dx, short dy, std::vector<Move>& moves, Board* b, bool ownAttack) const
{
	Point from = pos;
	while (true)
	{
		Point to = from;
		to.x += dx;
		to.y += dy;

		if (to.y == 8 || to.x == 8 || to.y == -1 || to.x == -1)
			return;

        if ((*b)[to] != NULL)
        {
            if ((*b)[to]->color != color || ownAttack)
                moves.push_back(Move(pos, to, TypeMove::attack, name));                            
            return;                
        }

		moves.push_back(Move(pos, to, TypeMove::move, name));
		from = to;
	}
}

std::vector<Move> Queen::getMoves(Board *b) const
{
    std::vector<Move> moves;

    findChess(0, 1, moves, b, false);
    findChess(0, -1, moves, b, false);
    findChess(1, 0, moves, b, false);
    findChess(-1, 0, moves, b, false);
    findChess(1, 1, moves, b, false);
    findChess(-1, -1, moves, b, false);
    findChess(1, -1, moves, b, false);    
    findChess(-1, 1, moves, b, false);

    return moves;
}

std::vector<Move> Queen::getControlCell(Board *b) const
{
    std::vector<Move> moves;

    findChess(0, 1, moves, b, true);
    findChess(0, -1, moves, b, true);
    findChess(1, 0, moves, b, true);
    findChess(-1, 0, moves, b, true);
    findChess(1, 1, moves, b, true);
    findChess(-1, -1, moves, b, true);
    findChess(1, -1, moves, b, true);    
    findChess(-1, 1, moves, b, true);

    return moves;
}

Figure* Queen::copy() const
{
    return new Queen(pos, color);    
}

double Queen::getCost() const
{
	if (color == FigureColor::white)
		return cost + costPos[7 - pos.y][pos.x];
	else
		return cost + costPos[pos.y][7 - pos.x];
}

bool Queen::isLegal(Role role, Board* b) const
{
	return true;
}