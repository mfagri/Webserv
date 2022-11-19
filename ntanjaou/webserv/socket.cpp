#include "socket.hpp"

Serv_Socket::Serv_Socket()
{};

Serv_Socket::Serv_Socket(int domain, int service, int protocol, int port, u_long interface, int back_log)
{
    //defining the structure's adress:
    this->address.sin_family = domain;
    this->address.sin_port = htons(port);
    this->address.sin_addr.s_addr = htonl(interface);
    //backlog is the number of possible connections
    this->bk_log = back_log;
    //estabilihsing the socket:
    //the socket
    this->sock = socket(domain, service, protocol);
    test_connection(this->sock);
    //binding the socket
    this->connection = Connect_to_network(get_socket(), get_adress());
    test_connection(this->connection);
    //start listetning
    Start_listening();
    test_connection(this->listening);
}

//function to test the connection:
void Serv_Socket::test_connection(int test)
{
    if(test < 0)
    {
        perror("Test has been failed !");
        exit(EXIT_FAILURE);
    }
}

int Serv_Socket::Connect_to_network(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
}

void Serv_Socket::Start_listening()
{
    this->listening = listen(get_socket(), this->bk_log);
}

//getter functions:
struct sockaddr_in Serv_Socket::get_adress() const
{
    return this->address;
}

int Serv_Socket::get_socket() const
{
    return this->sock;
}

int Serv_Socket::get_connection() const
{
    return this->connection;
}