/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:12:46 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/12/23 19:12:47 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_DATAX
#define REQUEST_DATAX

#include "general_info.hpp"

class DIY_req_data
{
private:
    int rd_org_skfd;
    int rd_sockfd;
    std::string rd_host;
    std::string rd_request;
    bool rd_endreq;
    bool rd_gotreq;
    size_t rd_size;
    int rd_numdata_readed;
    int rd_numdata_sended;
    size_t rd_req_len;
    
public:
    DIY_req_data();
    ~DIY_req_data() {};
    DIY_req_data(int rd_org_skfd ,int rd_sockfd, std::string rd_request, std::string rd_host);
    int get_rd_org_skfd() const;
    size_t get_rd_numdata_readed() const;
    size_t get_rd_numdata_sended() const;
    size_t get_rd_size() const;
    void set_rd_size(size_t value);
    size_t get_rd_reqlen() const;
    void set_rd_reqlen(size_t value);
    bool get_rd_rdgotreq() const;
    int get_rd_acceptfd() const;
    const std::string &get_rd_request();
    void set_rd_request(std::string str);
    void set_rd_numdata_readed(int value);
    void set_rd_numdata_sended(int value);
    void rd_append(char *str, size_t i);
    void set_rdgotreq(bool value);
};

#endif
