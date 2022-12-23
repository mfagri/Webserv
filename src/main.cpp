/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:34:23 by mmardi            #+#    #+#             */
/*   Updated: 2022/12/23 17:50:08 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

int main(int ac, char **av) {
    
    if (ac > 2) {
        
        std::cerr << "Too many arguments\n";
        return 1;
    }
    try
    {
        Parser parser(av);
        std::vector<ServerData> servers;
        servers = parser.getServers();

        DIY_server sv(servers);
        sv.launch_serv();
    }
    catch(const std::exception& e)
    {  
        std::cerr << e.what() << '\n';   
    }
}