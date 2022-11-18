#ifndef SERVER_HPP
#define SERVER_HPP

#include "socket.hpp"
#include <unistd.h>

class Serv
{
private:
    Serv_Socket * sock;
    int new_sock;
    char buffer[1024];
    void Accepter();
    void Handler();
    void Responder();
public:
    Serv();
    Serv(int domain, int service, int protocol, int port,
        u_long interface, int back_log);
    void Launcher();
    void test_connection(int test);
    Serv_Socket *get_sock() const;
};
#endif