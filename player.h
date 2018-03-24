#ifndef PLAYER_H
#define PLAYER_H

#include "message.h"
#include "manager.h"
#include "role.h"
//#include <iostream>

class Player {
public: 
    Player(Role role);
    void thinking();
    void recieveMessage();    

private: 
    
    Role role;
    double datumPos;
    
    double costFunc();    
    
    /**
     * @param m
     */
    void sendMessage(Message m);
};

#endif