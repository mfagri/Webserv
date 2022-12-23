#include "general_info.hpp"

DIY_req_data::DIY_req_data()
{
    this->rd_org_skfd = -1;
    this->rd_sockfd = -1;
    this->rd_host = "";
    this->rd_request = "";
    this->rd_endreq = false;
    this->rd_gotreq = false;
    this->rd_req_len = 0;
}

DIY_req_data::DIY_req_data(int orgsockfdRD, int sockfdRD, std::string requestRD, std::string hostRD)
{
    this->rd_org_skfd = orgsockfdRD;
    this->rd_sockfd = sockfdRD;
    this->rd_request = requestRD;
    this->rd_host = hostRD;
    this->rd_endreq = false;
    this->rd_gotreq = false;
    this->rd_size = 0;
    this->rd_numdata_readed = 0;
    this->rd_numdata_sended = 0;
    this->rd_req_len = 0;
}

int DIY_req_data::get_rd_org_skfd() const
{
    return this->rd_org_skfd;
}

size_t DIY_req_data::get_rd_numdata_readed() const
{
    return this->rd_numdata_readed;
}

size_t DIY_req_data::get_rd_numdata_sended() const
{
    return this->rd_numdata_sended;
}

void DIY_req_data::set_rd_numdata_readed(int value)
{
    this->rd_numdata_readed = value;
}

void DIY_req_data::set_rd_numdata_sended(int value)
{
    this->rd_numdata_sended = value;
}

void DIY_req_data::rd_append(char *str, size_t i)
{
    this->rd_request.append(str, i);
}

const std::string & DIY_req_data::get_rd_request()
{
    return this->rd_request;
}

bool DIY_req_data::get_rd_rdgotreq() const
{
    return this->rd_gotreq;
}

void DIY_req_data::set_rdgotreq(bool value)
{
    this->rd_gotreq = value;
}

int DIY_req_data::get_rd_acceptfd() const
{
    return this->rd_sockfd;
}

void DIY_req_data::set_rd_request(std::string str)
{
    this->rd_request = str;
}

size_t DIY_req_data::get_rd_size() const
{
    return this->rd_size;
}

void DIY_req_data::set_rd_size(size_t value)
{
    this->rd_size = value;
}

size_t DIY_req_data::get_rd_reqlen() const
{
    return this->rd_req_len;
}

void DIY_req_data::set_rd_reqlen(size_t value)
{
    this->rd_req_len = value;
}
