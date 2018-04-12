#include "position.h"
 
Position::Position(uint _maxDepth, Role _role): maxDepth(_maxDepth), whoseRole(_role), moveDepth(0) {};

int Position::getBestAssessment(Board* b, uint nowDepth)
{
	b->moveFigure(lastMove);
	assessment = costFunc(b);
	bestAssessment = assessment;

	short int k = 1;
	bool invert = true;

	if (nowDepth % 2 == 0)
	{
		k = -1;
		invert = false;
	}

	if (nowDepth == maxDepth)
	{
		moveDepth = nowDepth;	
		b->undoMove();
		return assessment*k;
	}

	canvass(b, (Role)(!whoseRole));

	for (uint i = 0; i < possibleMoves.size(); i++)
		if (possibleMoves[i].isAttack && (*b)[possibleMoves[i].to]->name == FigureName::king)
		{
			bestAssessment = -k*(checkmate - (int)nowDepth + (int)maxDepth);
			moveDepth = nowDepth;
			b->undoMove();
			return bestAssessment;
		}

	int tmp = 0;

	for (uint i = 0; i < possibleMoves.size(); i++)
	{
		Position* newPos = new Position(maxDepth, (Role)(!whoseRole));
		newPos->lastMove = possibleMoves[i];
		tmp = newPos->getBestAssessment(b, nowDepth + 1);		
		if (i == 0)
			bestAssessment = tmp;		
		if ((tmp > bestAssessment) ^ invert)
		{		
			bestAssessment = tmp;
			moveDepth = newPos->moveDepth;	
		}
		delete newPos;
	}

	//Проверка на пат
	if (b->getEnemyFigures(whoseRole).size() == 1)
	{
		Figure* fig = b->getEnemyFigures(whoseRole)[0];
		Position* newPos = new Position(maxDepth, (Role)(!whoseRole));

		//Создаем пустой ход
		newPos->lastMove = Move(fig->pos, fig->pos, false, fig->name);
		tmp = newPos->getBestAssessment(b, nowDepth + 1);

		//Ставим пат, только если на этом же этапе проверяли мат
		if (tmp < bestAssessment && bestAssessment >= checkmate && moveDepth == nowDepth + 1)
			bestAssessment = stalemate;
	}

	b->undoMove();

	return bestAssessment;
}

double Position::costFunc(Board* b)
{
	double cost = 0;	
	short int k = 1;

    for (uint i = 0; i < 8; i++)
		for (uint j = 0; j < 8; j++)
			if ((*b)[Point(i, j)] != NULL)
			{
				k = 1;
				if (whoseRole != (int)(*b)[Point(i, j)]->color)
					k = -1;
				cost += k*(*b)[Point(i, j)]->getCost();
			}
	return cost;
}

void Position::canvass(Board* b, Role role)
{
	std::vector<Figure*> ownFigure = b->getOwnFigures(role);
	std::vector<Move> tmpMove;

    for (uint i = 0; i < ownFigure.size(); i++)
	{
		tmpMove = ownFigure[i]->getMoves(b);
		for (uint j = 0; j < tmpMove.size(); j++)		
			possibleMoves.push_back(tmpMove[j]);			
	}
}