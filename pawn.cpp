#include "pawn.h"

Pawn::Pawn(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor, FigureName::pawn) {};

//Добавить превращение в другую фигуру и взятие на проходе
void Pawn::findChess(short dx, bool canAttack, std::vector<Move>& moves, Board* b) const
{
	Point from = pos;
	uint maxStep = 1;

	short dy = color == FigureColor::white ? 1 : -1;
	short initPosY = dy > 0 ? 1 : 6;

	if (initPosY == pos.y && !canAttack)
		maxStep = 2;

	for (int i = 0; i < maxStep; i++)
	{
		Point to = from;
		to.x += dx;
		to.y += dy;

		if (to.y == 8 || to.x == 8 || to.y == -1 || to.x == -1)
			return;

		if ((*b)[to] != NULL)
		{
			if ((*b)[to]->color != color && canAttack)
			{				
				if (to.y == 7 - initPosY + dy)
				{
					moves.push_back(Move(pos, to, true, FigureName::bishop));
					moves.push_back(Move(pos, to, true, FigureName::knight));
					moves.push_back(Move(pos, to, true, FigureName::rook));
					moves.push_back(Move(pos, to, true, FigureName::queen));
				}
				else
					moves.push_back(Move(pos, to, true, name));
			}
			return;
		}

		if (!canAttack)
		{
			if (to.y == 7 - initPosY + dy)
			{
				moves.push_back(Move(pos, to, false, FigureName::bishop));
				moves.push_back(Move(pos, to, false, FigureName::knight));
				moves.push_back(Move(pos, to, false, FigureName::rook));
				moves.push_back(Move(pos, to, false, FigureName::queen));
			}
			else
				moves.push_back(Move(pos, to, false, name));
		}
		from = to;
	}
}

std::vector<Move> Pawn::getMoves(Board *b) const
{
	std::vector<Move> moves;
	findChess(0, false, moves, b);
	findChess(1, true, moves, b);
	findChess(-1, true, moves, b);

	return moves;
}

Figure* Pawn::copy() const
{
	return new Pawn(pos, color);
}

double Pawn::getCost() const
{
	if (color == FigureColor::white)
		return cost + costPos[7 - pos.y][pos.x];
	else
		return cost + costPos[pos.y][7 - pos.x];
}

bool Pawn::isLegal(Role role) const
{
	return true;
}