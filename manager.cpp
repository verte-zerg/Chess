#include <condition_variable>
#include <thread>
#include <mutex>
#include "board.h"
#include <iostream>

#include "manager.h"

/**
 * Manager implementation
 */

extern Board* globalBoard;

extern Message* msg;
extern std::condition_variable checkMessage;
extern std::mutex lockAccess;

void Manager::update() {

}

void Manager::plot() {

}

void plotInConsole()
{
    std::cout << std::endl;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
            if ((*globalBoard)[Point(j, i)] != NULL)
            {
                std::string name;
                switch ((*globalBoard)[Point(j, i)]->name)
                {
                    case FigureName::pawn : name = " ";
                        break;
                    case FigureName::knight : name = "K";
                        break;
                    case FigureName::bishop : name = "B";
                        break;
                    case FigureName::rook : name = "R";
                        break;
                    case FigureName::queen : name = "Q";
                        break;
                    case FigureName::king : name = "W";
                        break;
                default:
                    break;
                }
                if ((*globalBoard)[Point(j, i)]->color == FigureColor::white)
                    name += "1"; 
                else
                    name += "2";
                std::cout << '|' << name << '|';
            }
            else
                std::cout << "|  |";
        std::cout << std::endl;
        for (uint k = 0; k < 8; k++)
            std::cout << "----";
        std::cout << std::endl;
    }
}

void Manager::sendMessage(Message* m) 
{
    std::unique_lock<std::mutex> locker(lockAccess);
    std::cout << "Менеджер отправил игроку " << ((state == 0) ? "Белый" : "Черный") << ".\n\n"; 
    msg = m;
}

void Manager::processingOfMessage()
{
    globalBoard->moveFigure(msg->move);
    plotInConsole();
    state = (Role)(!state);    
    Message* m = new Message(state, Move());
    
    std::this_thread::sleep_for(std::chrono::milliseconds{2000});
    
    sendMessage(m);

    checkMessage.notify_all();
}

void Manager::recieveMessage() 
{
    //Ожидание привязки всех на условную переменную
    std::this_thread::sleep_for(std::chrono::seconds{3});

    Message* m = new Message(Role::playerWhite, Move());   

    //Первый ход белых 
    state = Role::playerWhite;      

    sendMessage(m);

    checkMessage.notify_all();

    while (true)
    {
        std::unique_lock<std::mutex> locker(lockAccess);

        do
            checkMessage.wait(locker); 
        while (msg == NULL);

        if (msg->reciever != Role::manager)
        {
            std::cout << "Менеджер не принял." << std::endl;            
            locker.unlock();
            continue;
        }        

        if (msg->reciever == Role::manager)
        {
            std::cout << "Менеджер принял." << std::endl;                                   
            locker.unlock();   
            processingOfMessage();       
        }
    }
}