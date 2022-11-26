#include "general_info.hpp"

DIY_server::DIY_server(std::vector<ServerData> SV_d) : SV_data(SV_d)
{
    this->fd_sk_num = 0;
    this->sk_adr_len = sizeof(this->sk_address);
}

void DIY_server::init_sockets()
{
    size_t i = 0;
    std::vector<int> vec_ports;

    while (i < SV_data.size())
    {
        if (std::find(vec_ports.begin(), vec_ports.end(), SV_data[i].getPort()) != vec_ports.end())
        {
            continue;
            i++;
        }
        this->sk_list.push_back(DIY_socket());
        if (!(this->sk_list[i].Launch_sk(SV_data[i].getPort(), SV_data[i].getHost())))
        {
            continue;
            i++;
        }
        if (sk_list[i].listen_sk() < 0)
        {
            std::cout << "ERROR in socket !" << std::endl;
            shutdown(sk_list[i].get_sk(), SHUT_RDWR);
        }
        else
            vec_ports.push_back(SV_data[i].getPort());
        i++;
    }
}

int DIY_server::list_polls()
{
    int id_skfd;
    struct pollfd poll_fds;
    size_t i = -1;
    int num_pollfd = 0;

    while (++i < this->sk_list.size())
    {
        id_skfd = this->sk_list[i].get_sk();
        this->sk_fd.push_back(id_skfd);
        poll_fds.fd = id_skfd;
        poll_fds.events = POLLIN | POLLOUT;
        poll_fds.revents = 0;
        this->poll_list.push_back(poll_fds);
        this->fd_sk_num++;
        num_pollfd++;
    }
    return num_pollfd;
}

void DIY_server::del_sock(int sk_fd)
{
    int fd = this->poll_list[sk_fd].fd;
    close(fd);
    this->poll_list.erase(this->poll_list.begin() + sk_fd);
    this->fd_sk_num--;
}

std::string DIY_server::Req_buf_reader(int fd, int *n)
{
    int num_data_readed;
    int i = *n;
    *n = 0;
    char buffer[BUFFSIZE] = {0};
    std::string str_req;

    memset(buffer, 0, sizeof(buffer));
    num_data_readed = recv(fd, buffer, BUFFSIZE, 0);
    if(num_data_readed == 0)
    {
        this->del_sock(i);
        *n = 0;
    }
    else if(num_data_readed == -1)
    {
        this->del_sock(i);
        *n = -1;
    }
    else
    {
        str_req.append(buffer, num_data_readed);
        *n += num_data_readed;
    }
    return (str_req);
}

void DIY_server::Manager_I(int fd_plfdlist, int pos)
{
    // (void)pos;
    int sock_accept;
    int pos_sockfd = pos;
    std::string str_req;
    struct pollfd lst_pollfd;
    // char buff[1024] = {0};

    if (std::find(this->sk_fd.begin(), this->sk_fd.end(), fd_plfdlist) != this->sk_fd.end())
    {
        sock_accept = accept(fd_plfdlist, (struct sockaddr *)&this->sk_address, (socklen_t *)&this->sk_adr_len);
        if (sock_accept < 0)
        {
            std::cout << "error in accept !" << std::endl;
            return;
        }
        fcntl(sock_accept, F_SETFL, O_NONBLOCK);
        std::cout << "new connection has been set !" << std::endl;
        lst_pollfd.fd = sock_accept;
        lst_pollfd.events = POLLIN | POLLOUT;
        lst_pollfd.revents = 0;
        this->poll_list.push_back(lst_pollfd);
        this->fd_sk_num++;
    } 
    else 
    {
        // std::cout << read(fd_plfdlist, buff, BUFFSIZE);
        // std::cout << buff << std::endl;
        str_req = Req_buf_reader(fd_plfdlist, &pos_sockfd);
        std::cout << str_req << std::endl;
        // call request class here to process str_req
    }
}

void DIY_server::Manager_IO()
{
    int fd_from_pollfdList;
    size_t i = -1;

    while (1)
    {
        if (poll(&this->poll_list[0], this->fd_sk_num, -1) < 0)
            std::cerr << "Error in poll !" << std::endl;
        while (++i < this->poll_list.size())
        {
            fd_from_pollfdList = this->poll_list[i].fd;
            if (this->poll_list[i].revents & POLLIN)
            {
                Manager_I(fd_from_pollfdList, i);
            }
            // if(this->poll_list[i].revents & POLLOUT)
            // response function to be added later
        }
        i = -1;
    }
}

void DIY_server::launch_serv()
{
    std::cout << "Launching the PROGRAM !" << std::endl;
    init_sockets();
    if (list_polls() == 0)
    {
        std::cerr << "Not enough data to create a SERVER !" << std::endl;
        exit(EXIT_FAILURE);
    }
    Manager_IO();
}