#include "rook.h"

Rook::Rook(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor) {};

void Rook::findChess(short dx, short dy, std::vector<Move>& moves, Board* b) const
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
			if ((*b)[to]->color != color)
				moves.push_back(Move(pos, to, true, FigureName::rook));
			return;
		}

		moves.push_back(Move(pos, to, false, FigureName::rook));
		from = to;
	}
}

std::vector<Move> Rook::getMoves(Board *b) const
{
	std::vector<Move> moves;

	findChess(0, 1, moves, b);
    findChess(0, -1, moves, b);
	findChess(1, 0, moves, b);
	findChess(-1, 0, moves, b);
	
	return moves;
}

Figure* Rook::copy() const
{
	return new Rook(pos, color);
}