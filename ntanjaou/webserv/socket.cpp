#include "socket.hpp"

Serv_Socket::Serv_Socket(int domain, int service, int protocol, int port, u_long interface)
{
    //defining the structure's adress:
    this->address.sin_family = domain;
    this->address.sin_port = htons(port);
    this->address.sin_addr.s_addr = htonl(interface);
    //estabilihsing the socket:
    this->sock = socket(domain, service, protocol);
    test_connection(this->sock);
    this->connection = Connect_to_network(get_socket(), get_adress());
    test_connection(this->connection);
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