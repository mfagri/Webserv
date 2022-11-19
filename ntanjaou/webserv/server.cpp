#include "server.hpp"

Serv::Serv()
{
    int i = 0;
    while (i < 1024)
    {
        this->buffer[i++] = 0;
    }
}

Serv::Serv(int domain, int service, int protocol, int port, u_long interface, int back_log)
{
    this->sock = new Serv_Socket(domain, service, protocol,
                port, interface, back_log);
}

Serv_Socket * Serv::get_sock() const
{
    return this->sock;
}

void Serv::test_connection(int test)
{
    if(test < 0)
    {
        perror("Test has been failed !");
        exit(EXIT_FAILURE);
    }
}

void Serv::Accepter()
{
    struct sockaddr_in adr = this->sock->get_adress();
    int adr_len = sizeof(adr);
    this->new_sock = accept(this->sock->get_socket(), (struct sockaddr *)&adr, (socklen_t *) &adr_len);
    read(this->new_sock, this->buffer, 1024);
}

void Serv::Handler()
{
    std::cout << this->buffer << std::endl;
}

void Serv::Responder()
{
    write(this->new_sock, "Hello", 5);
    close(this->new_sock);
}

void Serv::Launcher()
{
    while(1)
    {
        std::cout << "------ Waiting ------" << std::endl;
        Accepter();
        test_connection(this->new_sock);
        Handler();
        Responder();
        std::cout << "--- Done ---" << std::endl;
    }
}