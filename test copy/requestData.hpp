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
    // int sendretsnd;
    int rd_numdata_readed;
public:
    DIY_req_data();
    ~DIY_req_data() {};
    DIY_req_data(int rd_org_skfd ,int rd_sockfd, std::string rd_request, std::string rd_host);
    int get_rd_org_skfd() const;
    size_t get_rd_numdata_readed() const;
    bool get_rd_rdgotreq() const;
    int get_rd_acceptfd() const;
    const std::string &get_rd_request();
    void set_rd_numdata_readed(int value);
    void rd_append(char *str, size_t i);
    void set_rdgotreq(bool value);


};

#endif
