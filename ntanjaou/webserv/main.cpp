#include "config.hpp"
#include "socket.hpp"
#include "server.hpp"

int main()
{
    // ConfigFile cf;
    // t_location lc;

    // lc.autoindex = "Off";
    // lc.index = "server1.html";
    // lc.allow_methods = "GET, POST, DELETE";
    // lc.fast_cgi_pass = "home/";
    // cf.Set_Cfile("2221", "0.0.0.0", "server1.com", 1024, "home/", lc);

    // std::cout << cf << std::endl;
    // Serv_Socket sv_sock;
    // std::cout << "Starting .." << std::endl;
    // std::cout << "Binding socket .." << std::endl;
    // std::cout << "Listening socket .." << std::endl;
    // sv_sock = Serv_Socket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    // std::cout << "Succes .." << std::endl;

    Serv s;
    s = Serv(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
    s.Launcher();
    return (0);
}
