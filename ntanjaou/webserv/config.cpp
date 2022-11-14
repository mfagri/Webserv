#include "config.hpp"

ConfigFile::ConfigFile()
{
    this->Listen = "";
    this->host = "";
    this->server_name = "";
    this->max_body_size = 0;
    this->root = "";
    this->location.autoindex = "";
    this->location.index = "";
    this->location.allow_methods = "";
    this->location.fast_cgi_pass = "";
}

void ConfigFile::Set_Cfile(str l, str h, str sn, int mbs, str r, t_location loc)
{
    this->Listen = l;
    this->host = h;
    this->server_name = sn;
    this->max_body_size = mbs;
    this->root = r;
    this->location = loc;
}

std::ostream & operator<<(std::ostream &out, ConfigFile const &cf)
{
    out << "Listen : " << cf.Listen << std::endl;
    out << "Host : " << cf.host << std::endl;
    out << "Server name : " << cf.server_name << std::endl;
    out << "Max body size : " << cf.max_body_size << std::endl;
    out << "Root : " << cf.root << std::endl;
    out << "Auto index : " << cf.location.autoindex << std::endl;
    out << "Index : " << cf.location.index << std::endl;
    out << "Allowed methods : " << cf.location.allow_methods << std::endl;
    out << "Fast cgi pass : " << cf.location.fast_cgi_pass << std::endl;
    return out;
}