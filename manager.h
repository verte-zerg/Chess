#ifndef MANAGER_H
#define MANAGER_H

#include "message.h"
#include "role.h"

void plotInConsole();

/**
 * @class Manager
 * @brief Класс менеджера, который отвечает за передачу хода между игроками и контролем хода игры
 */
class Manager 
{
private: 
    Role state;
    
    /**
     * @brief Функция отправки сообщения
     * 
     * @param m Сообщение, которое нужно отправить
     */
    void sendMessage(Message* m);

    /**
     * @brief Функция обработки полученного сообщения
     */
    void processingOfMessage();
public:

    /**
     * @brief Функция ожидания приёма сообщения
     */
    void recieveMessage();
};

#endif