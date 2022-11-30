#include "general_info.hpp"

DIY_req_data::DIY_req_data()
{
    this->rd_org_skfd = -1;
    this->rd_sockfd = -1;
    this->rd_host = "";
    this->rd_request = "";
    this->rd_endreq = false;
    this->rd_gotreq = false;
}

DIY_req_data::DIY_req_data(int orgsockfdRD, int sockfdRD, std::string requestRD, std::string hostRD)
{
    this->rd_org_skfd = orgsockfdRD;
    this->rd_sockfd = sockfdRD;
    this->rd_request = requestRD;
    this->rd_host = hostRD;
    this->rd_endreq = false;
    this->rd_size = 0;
    this->rd_numdata_readed = 0;
    // this->sendretsnd = 0;
}

int DIY_req_data::get_rd_org_skfd() const
{
    return this->rd_org_skfd;
}

size_t DIY_req_data::get_rd_numdata_readed() const
{
    return this->rd_numdata_readed;
}

void DIY_req_data::set_rd_numdata_readed(int value)
{
    this->rd_numdata_readed = value;
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
