#include "general_info.hpp"

int main(int ac, char **av) 
{
    if (ac > 2) {
        std::cerr << "Too many arguments\n";
        return 1;
    }
    try
    {
        std::vector<ServerData> servers;
        Parser parser(av);
        servers = parser.getServers();
        DIY_server sv(servers);
        sv.launch_serv();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}