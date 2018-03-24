#ifndef MESSAGE_END_MOVE_H
#define MESSAGE_END_MOVE_H

#include "message.h"

class MessageEndMove: public Message {
public: 
    Move move;
};

#endif