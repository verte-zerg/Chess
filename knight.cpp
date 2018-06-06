#include "knight.h"

Knight::Knight(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor, FigureName::knight, 0.) {};

void Knight::findChess(short dx, short dy, std::vector<Move>& moves, Board* b, bool ownAttack) const
{
	Point to = pos;
	to.x += dx;
	to.y += dy;

	if (to.y > 7 || to.x > 7 || to.y < 0 || to.x < 0)
		return;

	if ((*b)[to] != NULL)
	{
		if ((*b)[to]->color != color || ownAttack)
			moves.push_back(Move(pos, to, TypeMove::attack, name));		
		return;
	}

	moves.push_back(Move(pos, to, TypeMove::move, name));
}

std::vector<Move> Knight::getMoves(Board *b) const
{
	std::vector<Move> moves;

	findChess(1, 2, moves, b, false);
	findChess(2, 1, moves, b, false);
	findChess(2, -1, moves, b, false);
	findChess(1, -2, moves, b, false);
	findChess(-1, -2, moves, b, false);
	findChess(-2, -1, moves, b, false);
	findChess(-2, 1, moves, b, false);
	findChess(-1, 2, moves, b, false);

	return moves;
}

std::vector<Move> Knight::getControlCell(Board *b) const
{
	std::vector<Move> moves;

	findChess(1, 2, moves, b, true);
	findChess(2, 1, moves, b, true);
	findChess(2, -1, moves, b, true);
	findChess(1, -2, moves, b, true);
	findChess(-1, -2, moves, b, true);
	findChess(-2, -1, moves, b, true);
	findChess(-2, 1, moves, b, true);
	findChess(-1, 2, moves, b, true);

	return moves;
}

Figure* Knight::copy() const
{
	return new Knight(pos, color);
}

double Knight::getCost() const
{
	if (color == FigureColor::white)
		return cost + costPos[7 - pos.y][pos.x];
	else
		return cost + costPos[pos.y][7 - pos.x];
}

bool Knight::isLegal(Role role, Board* b) const
{
	return true;
}