#include "bishop.h"

Bishop::Bishop(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor) {};

void Bishop::findChess(short dx, short dy, std::vector<Move>& moves, Board* b) const
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
				moves.push_back(Move(pos, to, true, FigureName::bishop));
			else
				return;
		}

		moves.push_back(Move(pos, to, false, FigureName::bishop));
		from = to;
	}
}

std::vector<Move> Bishop::getMoves(Board *b) const
{
	std::vector<Move> moves;

	findChess(1, 1, moves, b);
    findChess(-1, -1, moves, b);
	findChess(1, -1, moves, b);	
	findChess(-1, 1, moves, b);	

	return moves;
}

Figure* Bishop::copy() const
{
	return new Bishop(pos, color);
}