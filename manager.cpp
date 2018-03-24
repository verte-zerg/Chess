/**
 * Project Chess
 */

#include <condition_variable>
#include <thread>
#include <mutex>
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
    Message* m = new Message();
    m->reciever = (Role)(!state);
    state = (Role)(!state);
    m->type = 2;
    
    std::this_thread::sleep_for(std::chrono::milliseconds{2000});
    
    sendMessage(m);

    checkMessage.notify_all();
}

/**
 * @return Message
 */
void Manager::recieveMessage() {
    std::this_thread::sleep_for(std::chrono::seconds{3});

    Message* m = new Message();
    m->reciever = Role::playerWhite;
    state = Role::playerWhite;
    m->type = 1;    

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