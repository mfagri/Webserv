/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:13:04 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/12/23 19:13:05 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "general_info.hpp"

class DIY_server
{
private:
    std::vector<ServerData> SV_data;
    std::vector<DIY_socket> sk_list;
    std::vector<int> sk_fd;
    std::vector<struct pollfd> poll_list;
    std::vector<DIY_req_data> RD_sock_accepted;
    Request sv_request;
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
    void Accept_req(int fd_plfdlist);
    void Manager_I(int fd_plfdlist, int curr_req);
    void Manager_O(int fd_plfdlist, int curr_req);
    void del_sock(int sk_fd);
    char *buff_request();
};

#endif