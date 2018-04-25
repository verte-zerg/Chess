#include "bishop.h"

Bishop::Bishop(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor, FigureName::bishop) {};

void Bishop::findChess(short dx, short dy, std::vector<Move>& moves, Board* b, bool ownAttack) const
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
				moves.push_back(Move(pos, to, true, name));
			return;
		}

		moves.push_back(Move(pos, to, false, name));
		from = to;
	}
}

std::vector<Move> Bishop::getMoves(Board *b) const
{
	std::vector<Move> moves;

	findChess(1, 1, moves, b, false);
    findChess(-1, -1, moves, b, false);
	findChess(1, -1, moves, b, false);	
	findChess(-1, 1, moves, b, false);	

	return moves;
}

std::vector<Move> Bishop::getControlCell(Board* b) const
{
	std::vector<Move> moves;

	findChess(1, 1, moves, b, true);
    findChess(-1, -1, moves, b, true);
	findChess(1, -1, moves, b, true);	
	findChess(-1, 1, moves, b, true);	

	return moves;
}

Figure* Bishop::copy() const
{
	return new Bishop(pos, color);
}

double Bishop::getCost() const
{	
	if (color == FigureColor::white)
		return cost + costPos[7 - pos.y][pos.x];
	else
		return cost + costPos[pos.y][7 - pos.x];	
}

bool Bishop::isLegal(Role role, Board* b) const
{
	return true;
}