#include <condition_variable>
#include <thread>
#include <mutex>
#include "board.h"
#include <iostream>

#include "manager.h"

/**
 * Manager implementation
 */

extern Message* msg;
extern std::condition_variable checkMessage;
extern std::mutex lockAccess;

void Manager::update() {

}

void Manager::plot() {

}

/**
 * @param m
 */
void Manager::sendMessage(Message* m) 
{
    std::unique_lock<std::mutex> locker(lockAccess);
    std::cout << "Менеджер отправил игроку " << ((state == 0) ? "Белый" : "Черный") << ".\n\n"; 
    msg = m;
}

void Manager::processingOfMessage()
{
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
            msg = NULL;
            locker.unlock();   
            processingOfMessage();       
        }
    }
}