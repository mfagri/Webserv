/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:34:23 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/21 14:10:05 by mmardi           ###   ########.fr       */
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
        std::vector<ServerData> servers;
        Parser parser(av);
        servers = parser.getServers();
        std::cout << servers[1].getHost() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
  
}