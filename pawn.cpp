#include "pawn.h"

Pawn::Pawn(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor, FigureName::pawn, 0.) {};

//Добавить превращение в другую фигуру и взятие на проходе
void Pawn::findChess(short dx, bool canAttack, std::vector<Move>& moves, Board* b, bool ownAttack) const
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

		if (canAttack && ownAttack)
		{
			moves.push_back(Move(pos, to, TypeMove::attack, name));
			return;
		}

		if ((*b)[to] != NULL)
		{			
			if ((*b)[to]->color != color && canAttack)
			{				
				if (to.y == 7 - initPosY + dy)
				{
					moves.push_back(Move(pos, to, TypeMove::attack_and_transform, FigureName::bishop));
					moves.push_back(Move(pos, to, TypeMove::attack_and_transform, FigureName::knight));
					moves.push_back(Move(pos, to, TypeMove::attack_and_transform, FigureName::rook));
					moves.push_back(Move(pos, to, TypeMove::attack_and_transform, FigureName::queen));
				}
				else
					moves.push_back(Move(pos, to, TypeMove::attack, name));
			}
			return;
		}		

		if (!canAttack)
		{
			if (to.y == 7 - initPosY + dy)
			{
				moves.push_back(Move(pos, to, TypeMove::transform, FigureName::bishop));
				moves.push_back(Move(pos, to, TypeMove::transform, FigureName::knight));
				moves.push_back(Move(pos, to, TypeMove::transform, FigureName::rook));
				moves.push_back(Move(pos, to, TypeMove::transform, FigureName::queen));
			}
			else
				moves.push_back(Move(pos, to, TypeMove::move, name));
		}
		from = to;
	}
}

std::vector<Move> Pawn::getMoves(Board *b) const
{
	std::vector<Move> moves;
	findChess(0, false, moves, b, false);
	findChess(1, true, moves, b, false);
	findChess(-1, true, moves, b, false);
	
	if (!b->movesHistory.empty() && b->movesHistory.back().figureName == pawn)
	{
		Move tmpM = b->movesHistory.back();
		if (abs(tmpM.to.y - tmpM.from.y) == 2 && pos.y == tmpM.to.y && abs(tmpM.to.x - pos.x) == 1)
		{
			short dy = ((tmpM.from.y - tmpM.to.y) > 0) ? 1 : -1;
			tmpM = Move(pos, Point(tmpM.to.x, tmpM.to.y + dy), en_passant, pawn);
			moves.push_back(tmpM);
		}
	}

	return moves;
}

std::vector<Move> Pawn::getControlCell(Board *b) const
{
	std::vector<Move> moves;	
	findChess(1, true, moves, b, true);
	findChess(-1, true, moves, b, true);

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

bool Pawn::isLegal(Role role, Board* b) const
{
	Point p1 = pos;
	Point p2 = pos;
	Point p3 = pos;

	bool checkPos = false;

	if (role == Role::playerWhite && pos.y == 2)
	{	
		p1.y -= 1;
		p2.y = p1.y;
		p3.y = p1.y;
		checkPos = true;
	}
	else if (role == Role::playerBlack && pos.y == 5)
	{	
		p1.y += 1;
		p2.y = p1.y;
		p3.y = p1.y;
		checkPos = true;
	}	

		if ((pos.x == 0 || pos.x == 7) && checkPos) 
		{
			if (p2.x == 0)
				p2.x += 1;
			
			if (p2.x == 7)
				p2.x -= 1;		

			if ((*b)[p1] != NULL && (*b)[p1]->name == FigureName::pawn && (*b)[p1]->color == color &&
				(*b)[p2] != NULL && (*b)[p2]->name == FigureName::pawn && (*b)[p2]->color == color)				
					return false;							
		}
		else if (pos.x > 0 && pos.x < 7 && checkPos)
		{	
			p1.x -= 1;
			p3.x += 1;

			if ((*b)[p1] != NULL && (*b)[p1]->name == FigureName::pawn && (*b)[p1]->color == color && 				
				(*b)[p2] != NULL && (*b)[p2]->name == FigureName::pawn && (*b)[p2]->color == color &&
					(*b)[p3] != NULL && (*b)[p3]->name == FigureName::pawn && (*b)[p3]->color == color)
						return false;
		}

		if (role == Role::playerWhite && pos.y == 0)
			return false;

		if (role == Role::playerBlack && pos.y == 7)
			return false;

	return true;
}