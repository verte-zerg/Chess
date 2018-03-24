/**
 * Project Chess
 */
#include <condition_variable>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

#include "player.h"


/**
 * Player implementation
 */

extern std::condition_variable checkMessage;
extern std::mutex lockAccess;
extern Message *msg;

Player::Player(Role _role):role(_role) {};

void Player::thinking() {
    
    Message* m = new Message();
    m->reciever = Role::manager;

    std::this_thread::sleep_for(std::chrono::milliseconds{3000});
    
    m->type = 2;
    
    std::unique_lock<std::mutex> locker(lockAccess);
    msg = m;   

    std::cout << "Игрок " << ((role == 0) ? "Белый" : "Черный") << " отправил менеджеру. " << std::endl; 

    checkMessage.notify_all();
}

/**
 * @return double
 */
double Player::costFunc() {
    return 0.0;
}

/**
 * @return Message
 */
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
            thinking();       
        }
    }
    
}

/**
 * @param m
 */
void Player::sendMessage(Message m) {
    
}