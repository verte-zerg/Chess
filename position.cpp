#include "position.h"
 
Position::Position(uint _depth, Role _role): depth(_depth), whoseRole(_role){
	if (depth == 0){		
		prev = this; //нужен указатель на ситуацию предыдущего хода ?
	}
}

void Position::canvass(Board* b){
	std::vector<Move> tmpMove;
	if (whoseRole == playerBlack)
	{
		for(uint i = 0; i < b->blackFigures.size(); i++) 
		{
			tmpMove = b->blackFigures[i]->getMoves(b);
			for (uint j = 0; j < tmpMove.size(); j++)		
			    possibleMoves.push_back(tmpMove[j]);

			tmpMove.clear();//??????????????????????????????
		}
	}


	if (whoseRole == playerWhite)
	{
		for(uint i = 0; i < b->whiteFigures.size(); i++)
		{
			tmpMove = b->whiteFigures[i]->getMoves(b);
			for (uint j = 0; j < tmpMove.size(); j++)		
				possibleMoves.push_back(tmpMove[j]);
							
			tmpMove.clear();
		}
	}
}

