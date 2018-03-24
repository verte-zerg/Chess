#ifndef MANAGER_H
#define MANAGER_H

#include "message.h"
#include "role.h"

class Manager {
private: 
    Role state;

    void plot();
    
    /**
     * @param m
     */
    void sendMessage(Message* m);

    void processingOfMessage();

    void update();
public:
    void recieveMessage();
};

#endif