#ifndef SERVER_HPP
#define SERVER_HPP

#include "general_info.hpp"

class DIY_server
{
private:
    //--> create later obj of request
    std::vector<ServerData> SV_data;
    std::vector<DIY_socket> sk_list;
    std::vector<int> sk_fd;
    std::vector<struct pollfd> poll_list;
    std::vector<int> sock_accepted;
    struct sockaddr_in sk_address;
    int sk_adr_len;
    int poll_sk;
    int fd_sk_num;
public:
    DIY_server(std::vector<ServerData> SV_d);
    void launch_serv();
    void init_sockets();
    int list_polls();
    std::string Req_buf_reader(int fd, int *n);
    void Manager_IO();
    void Manager_I(int fd_plfdlist, int pos);
    void del_sock(int sk_fd);
    char *buff_request();
};

#endif