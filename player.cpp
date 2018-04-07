#include <condition_variable>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

#include "player.h"
#include "message.h"

extern Board* globalBoard;

extern std::condition_variable checkMessage;
extern std::mutex lockAccess;
extern Message *msg;

Player::Player(Role _role, uint _calcDepth = 1): role(_role), calcDepth(_calcDepth) {};

double Player::costFunc(const Position* pos) 
{
    return 1.;
}

void Player::createPositions(Position* pos)
{ 
	if (pos->depth != 0) 
		ownBoard->moveFigure(pos->lastMove);

    if (pos->depth == calcDepth)
	{
		pos->bestAssessment = costFunc(pos);
		return;
	}

	pos->canvass(ownBoard);

    //Слежение за ролью
	Role r = ((pos->whoseRole == playerWhite) ? playerBlack : playerWhite);
	
	for(unsigned i = 0; i < pos->possibleMoves.size(); i++)
	{
		Position* pPos = new Position(pos->depth + 1, r); //когда удалится???
		pos->next.push_back(pPos);
		pPos->lastMove = pos->possibleMoves[i];
		pPos->prev = pos; 
		//pPos->assessment = costFunc(pPos);
		//if(pPos->badPos == true){
			//delete pPos;
		//}
		createPositions(pPos);
	}

	if(pos->depth != 0) 
		ownBoard->undoMove();

	pos->bestAssessment = pos->next[0]->bestAssessment;
	pos->bestNextMove = pos->next[0]->lastMove;

	//Почему минимизируется только для черного игрока!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if(pos->whoseRole == playerBlack)
	{
		for(uint i = 1; i < pos->next.size(); i++)
		{
			if(pos->next[i]->bestAssessment < pos->bestAssessment)
			{
				pos->bestAssessment = pos->next[i]->bestAssessment;
				pos->bestNextMove = pos->next[i]->lastMove;
			}
		}	
	}
	else
	{
		for(uint i = 1; i < pos->next.size(); i++)
		{
			if(pos->next[i]->bestAssessment > pos->bestAssessment)
			{
				pos->bestAssessment = pos->next[i]->bestAssessment;
				pos->bestNextMove = pos->next[i]->lastMove;
			}
		}
	}	
}


Message* Player::thinking() 
{
    ownBoard = new Board(*globalBoard);
    Position initPos(0, role);
    createPositions(&initPos);

    Message* m = new Message(Role::manager, initPos.bestNextMove);    

    //По приколу ждем
    std::this_thread::sleep_for(std::chrono::milliseconds{3000});        

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
            std::cout << "Игрок " << ((role == 0) ? "Белый" : "Черный") << " не принял. " << std::endl;            
            locker.unlock();
            continue;
        }

        if (msg->reciever == role)
        {
            std::cout << "Игрок " << ((role == 0) ? "Белый" : "Черный") << " принял. " << std::endl;                        
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

    std::cout << "Игрок " << ((role == 0) ? "Белый" : "Черный") << " отправил менеджеру. " << std::endl; 
    checkMessage.notify_all();
}