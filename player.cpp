#include <condition_variable>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

#include "player.h"
#include "message.h"
#include "stateGame.h"

extern Board* globalBoard;

extern std::condition_variable checkMessage;
extern std::mutex lockAccess;
extern Message *msg;
extern StateGame stateGame;

Player::Player(Role _role, uint _calcDepth = 1): role(_role), calcDepth(_calcDepth) {};

double Player::costFunc(const Position* pos)
{
	int cost = 0;	
	short int k = 1;

    for (uint i = 0; i < 8; i++)
		for (uint j = 0; j < 8; j++)
			if ((*ownBoard)[Point(i, j)] != NULL)
			{
				if (role == (int)(*ownBoard)[Point(i, j)]->color)
					k = 1;
				else
					k = -1;
				switch ((*ownBoard)[Point(i, j)]->name)
				{
					case FigureName::pawn : cost += 10*k;
						break;
					case FigureName::knight : cost += 30*k;
						break;
					case FigureName::bishop : cost += 30*k;
						break;
					case FigureName::rook : cost += 50*k;
						break;
					case FigureName::queen : cost += 90*k;
						break;
					case FigureName::king : cost += 9000*k;
						break;
				}
			}
	return cost;
}

Move Player::getBestMove()
{ 
	Position initPos(calcDepth, role);
	initPos.canvass(ownBoard, role);

	Move bestMove = initPos.possibleMoves[0];
	int bestAssessment = -1.e8;
	int tmp;	

	for (uint i = 0; i < initPos.possibleMoves.size(); i++)
	{
		Position* newPos = new Position(calcDepth, role);
		newPos->lastMove = initPos.possibleMoves[i];
		tmp = newPos->getBestAssessment(ownBoard, 1);
		//std::cout << "Move: " << newPos->lastMove << "; Cost: " << tmp << std::endl;
		if (tmp > bestAssessment)	
		{	
			bestAssessment = tmp;	
			bestMove = newPos->lastMove;
		}	
		delete newPos;
	}

	if (bestAssessment >= initPos.checkmate + (int)calcDepth - 2 - (((int)calcDepth + 1) % 2))
	{
		std::cout << "Мат поставил игрок " << ((role == Role::playerWhite) ? "Белый" : "Черный") << std::endl;
		stateGame = StateGame::checkmate;
	}
	else if (bestAssessment >= initPos.stalemate + (int)calcDepth - 2 - (((int)calcDepth + 1) % 2) && bestAssessment < initPos.checkmate)
	{
		std::cout << "Пат поставил игрок " << ((role == Role::playerWhite) ? "Белый" : "Черный") << std::endl;
		stateGame = StateGame::stalemate;
	}
	
	return bestMove;
}


Message* Player::thinking() 
{
    ownBoard = new Board(*globalBoard);
    Message* m = new Message(Role::manager, Player::getBestMove());    

    //Просто ждем
    std::this_thread::sleep_for(std::chrono::milliseconds{2000});        

    return m;
}


void Player::recieveMessage() {    
    while (true)
    {
        std::unique_lock<std::mutex> locker(lockAccess);
        do
            checkMessage.wait(locker); 
        while (msg == NULL);       

        if (msg->reciever != role)
        {
            //std::cout << "Игрок " << ((role == 0) ? "Белый" : "Черный") << " не принял. " << std::endl;  
            locker.unlock();
            continue;
        }

        if (msg->reciever == role)
        {
            //std::cout << "Игрок " << ((role == 0) ? "Белый" : "Черный") << " принял. " << std::endl;                        
            msg = NULL;
            locker.unlock();            
            sendMessage(thinking());               
        }
    }
}

void Player::sendMessage(Message* m) 
{
    std::unique_lock<std::mutex> locker(lockAccess);
    msg = m;   

    std::cout << "Игрок " << ((role == 0) ? "Белый" : "Черный") << ": " << m->move << std::endl; 
    checkMessage.notify_all();
}