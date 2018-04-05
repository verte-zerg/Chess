#include "pawn.h"

Pawn::Pawn(Point _pos, FigureColor _figureColor) : Figure(_pos, _figureColor) {};

std::vector<Move> Pawn::getMoves(Board *b) const
{
	std::vector<Move> moves;

	return moves;
}

Figure* Pawn::copy() const
{
	return new Pawn(pos, color);
}