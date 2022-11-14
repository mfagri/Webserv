#include "config.hpp"

int main()
{
    ConfigFile cf;
    t_location lc;

    lc.autoindex = "Off";
    lc.index = "server1.html";
    lc.allow_methods = "GET, POST, DELETE";
    lc.fast_cgi_pass = "home/";
    cf.Set_Cfile("2221", "0.0.0.0", "server1.com", 1024, "home/", lc);

    std::cout << cf << std::endl;
    return (0);
}
