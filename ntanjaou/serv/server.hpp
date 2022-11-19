#ifndef SERVER_HPP
#define SERVER_HPP

#include "general_info.hpp"

class DIY_server
{
private:
    //--> create later a vector of server data
    //--> create later obj of request
    //--> create later obj of IO handling
    std::vector<DIY_socket> sk_list;
    std::vector<int> sk_fd;
    std::vector<struct pollfd> poll_list;
    struct sockaddr_in sk_address;
    int sk_adr_len;
    int poll_sk;
    int fd_sk_num;
public:
    //create later constructor with server data as parameter
    void launch_serv();
    void init_sockets();
    int list_polls();
    void del_sock(int sk_fd);
    char *buff_request();
};

#endif