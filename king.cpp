#include "king.h"

King::King(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor, FigureName::king) {};

void King::findChess(short dx, short dy, std::vector<Move>& moves, Board* b) const
{
	Point to = pos;
	to.x += dx;
	to.y += dy;

	if (to.y == 8 || to.x == 8 || to.y == -1 || to.x == -1)
		return;

	if ((*b)[to] != NULL)
	{
		if ((*b)[to]->color != color)
			moves.push_back(Move(pos, to, true, FigureName::king));
		else
			return;
	}

	moves.push_back(Move(pos, to, false, FigureName::king));
}

std::vector<Move> King::getMoves(Board *b) const
{
	std::vector<Move> moves;

	findChess(0, 1, moves, b);
	findChess(0, -1, moves, b);
	findChess(1, 0, moves, b);
	findChess(-1, 0, moves, b);
	findChess(1, 1, moves, b);
	findChess(-1, -1, moves, b);
	findChess(1, -1, moves, b);	
	findChess(-1, 1, moves, b);

	return moves;
}

Figure* King::copy() const
{
	return new King(pos, color);
}