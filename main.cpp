#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>

#include "board.h"
#include "player.h"
#include "manager.h"
#include "point.h"
#include "figureColor.h"
#include "allFigures.h"

Message* msg = NULL;
std::condition_variable checkMessage;
std::mutex lockAccess;

int main()
{
    Player playerWhite(Role::playerWhite), playerBlack(Role::playerBlack);
    Manager manager;

    std::thread mng(&Manager::recieveMessage, std::ref(manager));
    std::thread plW(&Player::recieveMessage, std::ref(playerWhite));
    std::thread plB(&Player::recieveMessage, std::ref(playerBlack));

    mng.join();
    plW.join();
    plB.join();

    return 0;
}