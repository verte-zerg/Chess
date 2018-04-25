#include "king.h"

King::King(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor, FigureName::king), countStep(0) {};

void King::findChess(short dx, short dy, std::vector<Move>& moves, Board* b, bool ownAttack) const
{
	Point to = pos;
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
}

std::vector<Move> King::getMoves(Board *b) const
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

std::vector<Move> King::getControlCell(Board *b) const
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

Figure* King::copy() const
{	
	King* newKing = new King(pos, color);
	newKing->countStep = countStep;	
	return newKing;
}

double King::getCost() const
{
	if (color == FigureColor::white)
		return cost + costPos[7 - pos.y][pos.x];
	else
		return cost + costPos[pos.y][7 - pos.x];
}

bool King::isLegal(Role role, Board* b) const
{
	return true;
}