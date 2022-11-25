/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:34:23 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/25 19:09:35 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include "Parser.hpp"
# include "ServerData.hpp"

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
        std::vector<std::map<std::string, std::string>> locations = servers[0].getLocations();
        std::cout << locations.size() << std::endl;  
        std::cout << locations[0].at("location-path") << std::endl;  
        std::cout << locations[0].at("upload_enable") << std::endl;  
    }
    catch(const std::exception& e)
    {
        
        std::cerr << e.what() << '\n';
        
    }
}