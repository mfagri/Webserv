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


size_t check_content_len(std::string request)
{
    size_t pos = 0;
    size_t find_pos = 0;
    size_t end_pos = request.find("\n");

    while (end_pos != std::string::npos)
    {
        std::string l = request.substr(pos, end_pos - pos);

        if ((find_pos = l.find("Content-Length:")) != std::string::npos && find_pos == 0)
            return (atoi(l.substr(l.find(":") + 2, l.length()).c_str()));
        else if ((find_pos = l.find("\r\n\r\n")) != std::string::npos && find_pos == 0)
            return (0);

        pos = end_pos + 1;
        end_pos = request.find("\n", pos);
    }
    return (0);
}

int check_req_content(std::string request)
{
    size_t begin = 0;
    size_t find_pos = 0;
    size_t end = request.find("\r\n");

    while(end != std::string::npos)
    {
        std::string header = request.substr(begin, end - begin);
        if ((find_pos = header.find("Transfer-Encoding: chunked")) != std::string::npos && find_pos == 0)
            return (2);
        else if ((find_pos = header.find("Content-Length")) != std::string::npos && find_pos == 0)
            return (1);
        else if ((find_pos = header.find("\r\n\r\n")) != std::string::npos && find_pos == 0)
            return (0);
        begin = end + 1;
        end = request.find("\n", begin);
    }
    return (0);
}

bool check_request(DIY_req_data rd_request)
{
    int req_status;
    std::string request;
    size_t pos;
    std::string rq_body;

    request = rd_request.get_rd_request();
    req_status = check_req_content(request);
    pos = request.find("\r\n\r\n");

    if(req_status == 0 && pos != std::string::npos){
        return true;
    }
    if(req_status == 1)
    {
        rq_body = request.substr(pos + 4, request.length() - (pos + 4));
        // printf("%lu , %lu \n", rd_request.get_rd_numdata_readed() - (pos + 4), check_content_len(request));
        if(rd_request.get_rd_numdata_readed() - (pos + 4) == check_content_len(request)){
            return true;
        }
        // if(rd_request.get_rd_numdata_readed() - (pos + 4) >= check_content_len(request))
        // {
        //     return true;
        // }
    }
    if(req_status == 2)
    {
        rq_body = request.substr(pos + 4, request.length() - (pos + 4));
        pos = request.find("0\r\n\r\n");
        if(pos != std::string::npos)
        {
            if(pos){
                return true;
            }
        }
    }
    return false;
}

void DIY_server::Accept_req(int fd_plfdlist)
{
    int sock_accept;
    struct pollfd lst_pollfd;

    sock_accept = accept(fd_plfdlist, (struct sockaddr *)&this->sk_address, (socklen_t *)&this->sk_adr_len);
    if (sock_accept < 0)
    {
        std::cout << "error in accept !" << std::endl;
        return ;
    }
    fcntl(sock_accept, F_SETFL, O_NONBLOCK);
    std::cout << "New connection has been set ! socket : " << fd_plfdlist << " accepted at : " << sock_accept << std::endl;
    lst_pollfd.fd = sock_accept;
    lst_pollfd.events = POLLIN | POLLOUT;
    lst_pollfd.revents = 0;
    this->poll_list.push_back(lst_pollfd);
    this->fd_sk_num++;
    this->RD_sock_accepted.push_back(DIY_req_data(fd_plfdlist , sock_accept, "", inet_ntoa(this->sk_address.sin_addr)));
}

void DIY_server::Manager_I(int fd_plfdlist, int curr_req)
{
    int index = 0;
    char buff[BUFFSIZE];
    bzero(buff, sizeof(buff));
    int num_data_readed = 0;
    if(std::find(this->sk_fd.begin(), this->sk_fd.end(), fd_plfdlist) != this->sk_fd.end()){
        Accept_req(fd_plfdlist);
    }
    else
    {
        for (size_t i = 0; i < this->RD_sock_accepted.size(); i++)
        {
            if (this->RD_sock_accepted[i].get_rd_acceptfd() == fd_plfdlist){   
                index = i;
                break;
            }
        }
        num_data_readed = recv(fd_plfdlist, buff, BUFFSIZE, 0);
        // std::cout << "num data readed : " << num_data_readed << std::endl;
        // std::cout << "*************************************** " << std::endl;
        // std::cout << buff << std::endl;
        // std::cout << "------------------------------------- " << std::endl;
        this->RD_sock_accepted[index].set_rd_numdata_readed(this->RD_sock_accepted[index].get_rd_numdata_readed() + num_data_readed);
        if(num_data_readed < 1)
        {
            std::cout << "This socket has been disconnected : " << fd_plfdlist << std::endl;
            close(fd_plfdlist);
            this->poll_list.erase(this->poll_list.begin() + curr_req);
            this->RD_sock_accepted.erase(this->RD_sock_accepted.begin() + index);
            this->fd_sk_num--;
        }
        else if(num_data_readed > 0)
        {
            this->RD_sock_accepted[index].rd_append(buff, num_data_readed);
            this->RD_sock_accepted[index].set_rdgotreq(check_request(this->RD_sock_accepted[index]));
            // std::cout << " <| " << this->RD_sock_accepted[index].get_rd_request() << " |> " <<  std::endl;
            if(this->RD_sock_accepted[index].get_rd_rdgotreq() == true)
            {
                // puts("here");
                //printf("my request lenght is : %lu \n", this->RD_sock_accepted[index].get_rd_request().length());
                //puts("in req");
                // std::cout<<this->RD_sock_accepted[index].get_rd_request()<<std::endl;
                // puts("in request");
                Request req(this->RD_sock_accepted[index].get_rd_request());
                this->sv_request = req;
                // Response resp(this->sv_request);
                // std::string test;
                // test = resp.get_res();
                // this->RD_sock_accepted[index].set_rd_request(test);
            }
        }
        this->poll_list[curr_req].events = POLLIN | POLLOUT;
    }
}

void DIY_server::Manager_O(int fd_plfdlist, int curr_req)
{
    int index = 0;

    for (size_t i = 0; i < this->RD_sock_accepted.size(); i++)
    {
        if (this->RD_sock_accepted[i].get_rd_acceptfd() == fd_plfdlist){   
            index = i;
            break;
        }
    }
    if(this->RD_sock_accepted[index].get_rd_rdgotreq() == true)
    {
        // puts("in response");
        int num_data_sended = 0;
        std::string resp;
        Response respp(this->sv_request, SV_data);
        this->RD_sock_accepted[index].set_rd_request(respp.get_res());
        resp = this->RD_sock_accepted[index].get_rd_request();
        this->RD_sock_accepted[index].set_rd_size(resp.length());
        int len = this->RD_sock_accepted[index].get_rd_size();
        num_data_sended = send(fd_plfdlist, resp.c_str(), len, 0);
        this->RD_sock_accepted[index].set_rd_numdata_sended(this->RD_sock_accepted[index].get_rd_numdata_sended() + num_data_sended);
        try
        {
            this->RD_sock_accepted[index].set_rd_request(this->RD_sock_accepted[index].get_rd_request().substr(num_data_sended));
        }
        catch(std::exception &e)
        {
            num_data_sended = -1;
        }
        // printf("num data : %d and request lenght : %lu \n", num_data_sended, this->RD_sock_accepted[index].get_rd_size());
        if(num_data_sended < 1 || (int)this->RD_sock_accepted[index].get_rd_request().length() == num_data_sended)
        {
            std::cout << "This socket has been disconnected : " << fd_plfdlist << std::endl;
            close(fd_plfdlist);
            this->poll_list.erase(this->poll_list.begin() + curr_req);
            this->RD_sock_accepted.erase(this->RD_sock_accepted.begin() + index);
            this->fd_sk_num--;
        }
        // this->RD_sock_accepted[index].set_rdgotreq(false);
        // this->RD_sock_accepted[index].set_rd_request("");
    }
    this->poll_list[curr_req].events = POLLIN;
    this->poll_list[curr_req].revents = 0;
}

void DIY_server::Manager_IO()
{
    int fd_from_pollfdList;
    size_t i = -1;
    std::string catch_req;

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
            if(this->poll_list[i].revents & POLLHUP)
            {
                int index;
                index = 0;
                for (size_t k = 0; k < this->RD_sock_accepted.size(); k++)
                {
                    if (this->RD_sock_accepted[k].get_rd_acceptfd() == fd_from_pollfdList)
                    {   
                        index = k;
                        break;
                    }
                }
                if(index)
                {
                    std::cout << "This socket has been disconnected : " << fd_from_pollfdList << std::endl;
                    close(fd_from_pollfdList);
                    this->poll_list.erase(this->poll_list.begin() + i);
                    this->RD_sock_accepted.erase(this->RD_sock_accepted.begin() + index);
                    this->fd_sk_num--;
                }
            }
            if (this->poll_list[i].revents & POLLOUT)
            {
                Manager_O(fd_from_pollfdList, i);
            }
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