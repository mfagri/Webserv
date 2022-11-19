#include "socket.hpp"

DIY_socket::DIY_socket()
{

}

DIY_socket::~DIY_socket(){};

void DIY_socket::test_cnx_sk(int test)
{
    if(test < 0)
    {
        perror("test has failed !");
        exit(EXIT_FAILURE);
    }
}

int DIY_socket::Launch_sk(int port, std::string host)
{
    this->socket_FD = socket(AF_INET, SOCK_STREAM, 0);
    if(this->socket_FD < 0)
    {
        std::cerr << "error !" << std::endl;
        return -1;
    }
    this->address_sk_len = sizeof(this->address_sk);
    Bind_sk(port, host);
    fcntl(this->socket_FD, F_SETFL, O_NONBLOCK);
}


void DIY_socket::Bind_sk(int port, std::string interface)
{
    this->address_sk.sin_family = AF_INET;
    this->address_sk.sin_port = htons(port);
    this->address_sk.sin_addr.s_addr = htonl(INADDR_ANY);
    int opt = 1;
    test_cnx_sk(setsockopt(this->socket_FD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)));
    test_cnx_sk(bind(this->socket_FD, (struct sockaddr *)& this->address_sk, this->address_sk_len));
}

int DIY_socket::listen_sk()
{
    int lst_sk = 0;
    if(this->socket_FD)
        lst_sk = listen(this->socket_FD, 0);
    return lst_sk;
}

int DIY_socket::get_sk() const
{
    return this->socket_FD;
}

struct sockaddr_in DIY_socket::get_adr_sk() const
{
    return this->address_sk;
}