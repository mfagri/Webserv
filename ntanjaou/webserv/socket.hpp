#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>


class Serv_Socket
{
private:
    struct sockaddr_in address;
    int sock;
    int connection;
    int bk_log;
    int listening;

public:
    Serv_Socket();
    Serv_Socket(int domain, int service, int protocol, int port,
                u_long interface, int back_log);
    int Connect_to_network(int sock, struct sockaddr_in address);
    void Start_listening();
    void test_connection(int test);
    struct sockaddr_in get_adress() const;
    int get_socket() const;
    int get_connection() const;
};


#endif
