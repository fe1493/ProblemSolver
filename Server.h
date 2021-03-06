//
// Created by yonatan on 14/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

/*
 * Server interface
 */

#include "MyTestClientHandler.h"


namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler* clientHandler) = 0;

        virtual void stop() = 0;
    };
}

#endif //EX4_SERVER_H
