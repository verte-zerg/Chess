#include "king.h"
#include <cmath>

King::King(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor, FigureName::king, 0.), countStep(0) {};

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
			moves.push_back(Move(pos, to, TypeMove::attack, name));	
		return;
	}

	moves.push_back(Move(pos, to, TypeMove::move, name));
}

void King::isLegalCastling(std::vector<Move>& moves, Board* b, Point posOfRook) const
{
	if ((*b)[posOfRook] != NULL && (*b)[posOfRook]->name == rook && (*b)[posOfRook]->color == color) 
	{
		if (((Rook*)(*b)[posOfRook])->countStep == 0) 
		{
			short from, to;
			bool f = true;

			if (posOfRook.x == 7) 
			{ 
				from = 5; 
				to = 7;
			} 
			if (posOfRook.x == 0) 
			{ 
				from = 1; 
				to = 4;
			} 
			for (short x = from; x < to; x++) 
			{
				if ((*b)[Point(x,posOfRook.y)] != NULL) 
				{
					f = false;
					break;
				}
			}
			if (f) 
			{
				if (from == 5)
				{
					from = 4;
					to = 6;
				}
				else
				{
					from = 1; 
					to = 4;
				}

				for (short x = from; x <= to; x++) 
				{
					if (b->cellIsAttacked(Point(from, posOfRook.y), (Role)color) == true) 
					{
						f = false;
						break;
					}
				}
				if (f) 
					moves.push_back(Move(pos, posOfRook, TypeMove::castling, king));
			}
		}
	}
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

	if (countStep == 0) 
	{
		if (color == white) 
		{
			isLegalCastling(moves, b, Point(7,0));
			isLegalCastling(moves, b, Point(0,0));
		}
		if (color == black) 
		{
			isLegalCastling(moves, b, Point(7,7));
			isLegalCastling(moves, b, Point(0,7));
		}
	}

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
	Point pointKing; 
	std::vector<Figure*> enemyFigures = b->getEnemyFigures((Role) color); 
	
	for (unsigned i = 0; i < enemyFigures.size(); i++) 
		if (enemyFigures[i]->name == king) 
			pointKing = enemyFigures[i]->pos; 
	
	double length = std::sqrt(std::pow(pos.y - pointKing.y, 2) + std::pow(pos.x - pointKing.x, 2)); 
	if (length < 1.9) 
		return false; 
	
	return true;
}