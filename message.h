#ifndef MESSAGE_H
#define MESSAGE_H

#include "role.h"
#include "move.h"

class Message {
public: 
    Role reciever; 
    Move move;

    Message(Role _reciever, Move _move): move(_move), reciever(_reciever) {};

    Message(const Message& m)
    {
        reciever = m.reciever;
        move = m.move;
    }
};

#endif